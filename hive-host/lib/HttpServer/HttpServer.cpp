#include "HttpServer.h"

HttpServer::HttpServer() : server(80)
{
}

HttpServer *HttpServer::GetInstance()
{
    static HttpServer *s = new HttpServer();
    return s;
}

void HttpServer::Init()
{
    SPIFFS.begin();
    {
        Serial.println("SPIFFS contents:");

        Dir dir = SPIFFS.openDir("/");
        while (dir.next())
        {
            String fileName = dir.fileName();
            size_t fileSize = dir.fileSize();
            Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
        }
        Serial.printf("\n");
    }

    server.serveStatic("/", SPIFFS, "/index.html", "max-age=86400");
    server.onNotFound([this]() {
        if (!m_HandleFileRead(server.uri()))
            server.send(404, "text/plain", "FileNotFound");
    });
    server.begin();
}

void HttpServer::Update()
{
    server.handleClient();
}

bool HttpServer::HandleFileRead(String path)
{
    Serial.println("handleFileRead: " + path);

    if (path.endsWith("/"))
        path += "index.html";

    String contentType = GetContentType(path);
    String pathWithGz = path + ".gz";

    if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
    {
        if (SPIFFS.exists(pathWithGz))
            path += ".gz";

        File file = SPIFFS.open(path, "r");
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.streamFile(file, contentType);
        file.close();

        return true;
    }
    return false;
}

String HttpServer::GetContentType(String filename)
{
    if (server.hasArg("download"))
        return "application/octet-stream";
    else if (filename.endsWith(".htm"))
        return "text/html";
    else if (filename.endsWith(".html"))
        return "text/html";
    else if (filename.endsWith(".css"))
        return "text/css";
    else if (filename.endsWith(".js"))
        return "application/javascript";
    else if (filename.endsWith(".png"))
        return "image/png";
    else if (filename.endsWith(".gif"))
        return "image/gif";
    else if (filename.endsWith(".jpg"))
        return "image/jpeg";
    else if (filename.endsWith(".ico"))
        return "image/x-icon";
    else if (filename.endsWith(".xml"))
        return "text/xml";
    else if (filename.endsWith(".pdf"))
        return "application/x-pdf";
    else if (filename.endsWith(".zip"))
        return "application/x-zip";
    else if (filename.endsWith(".gz"))
        return "application/x-gzip";
    return "text/plain";
}

bool HttpServer::m_HandleFileRead(String path)
{
    return HttpServer::GetInstance()->HandleFileRead(path);
}