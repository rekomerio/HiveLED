import { useRef } from "react";

const useSocket = (url: string): WebSocket => {
    const socket = useRef<WebSocket>(new WebSocket(url));

    return socket.current;
};

export default useSocket;
