import { WS_URL } from "../config";

// Global Websocket for all components
export let webSocket = new WebSocket(WS_URL);

// Creates new instance of the socket
export const reconnectSocket = () => {
    if (webSocket.readyState === WebSocket.OPEN) {
        webSocket.close();
    }
    webSocket = new WebSocket(WS_URL);
};
