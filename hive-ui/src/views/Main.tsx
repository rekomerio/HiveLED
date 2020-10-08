import React, { useRef, useState, useEffect } from "react";
import Client from "../components/Client";

export interface MainProps {}

const Main = () => {
    const [isConnected, setIsConnected] = useState<boolean>(false);
    const socket = useRef<WebSocket>(new WebSocket("ws://192.168.43.26:81"));

    useEffect(() => {
        socket.current.addEventListener("open", (e) => {
            console.log("connected", e);
            setIsConnected(true);
        });

        socket.current.addEventListener("close", (e) => {
            console.log("disconnected", e);
            setIsConnected(false);
        });

        socket.current.addEventListener("message", (e) => {
            console.log("new message", e);

            if (typeof e.data === "object") {
                e.data.bufferArray().then((res) => {
                    const arr = new Uint8Array(res);
                    console.log(arr);
                });
            } else {
                console.log(e.data.split(";"));
            }
        });
    }, []);

    return (
        <div>
            {[0].map((client, i) => (
                <Client key={i} id={i} socket={socket.current} />
            ))}
        </div>
    );
};

export default Main;
