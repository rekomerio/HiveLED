#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <ESP8266WebServer.h>

class HttpServer
{
public:
    static HttpServer *GetInstance();
    void Init();
    void Update();

private:
    HttpServer();

    bool HandleFileRead(String path);
    static bool m_HandleFileRead(String path);
    String GetContentType(String filename);

    ESP8266WebServer server;
};

#endif