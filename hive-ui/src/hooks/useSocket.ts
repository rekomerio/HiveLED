import { useEffect, useState, useRef, useMemo } from "react";

interface UseSocket {
    onOpen: (e: Event) => void;
    onClose: (e: CloseEvent) => void;
    onMessage: (e: MessageEvent) => void;
}

const useSocket = (socketFunctions: UseSocket, url: string) => {
    const socket = useRef<WebSocket>(new WebSocket(url));
    const [isConnected, setIsConnected] = useState<boolean>(false);

    useEffect(() => {
        socket.current.addEventListener("open", (e) => {
            socketFunctions.onOpen(e);
            setIsConnected(true);
        });

        socket.current.addEventListener("close", (e) => {
            socketFunctions.onClose(e);
            setIsConnected(false);
        });

        socket.current.addEventListener("message", (e) => {
            socketFunctions.onMessage(e);
        });

        return socket.current.close;
    }, []);

    return useMemo(
        () => ({
            socket: socket.current,
            isConnected,
        }),
        [socket.current, isConnected]
    );
};

export default useSocket;
