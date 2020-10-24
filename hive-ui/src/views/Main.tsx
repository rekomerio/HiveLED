import React, { useRef, useState, useEffect } from "react";
import { Box, makeStyles } from "@material-ui/core";
import Client from "../components/Client";
import { Option } from "../helpers/types";

export interface MainProps {}

const useStyles = makeStyles((theme) => ({
    root: {
        height: "100%",
        minHeight: "100vh",
        backgroundColor: theme.palette.background.default,
    },
}));

const Main = () => {
    const classes = useStyles();
    const [isConnected, setIsConnected] = useState<boolean>(false);
    const [effects, setEffects] = useState<Option[]>([]);
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
            } else if (typeof e.data === "string" && e.data.startsWith("[")) {
                console.log(JSON.parse(e.data));

                const options: Option[] = Object.keys(JSON.parse(e.data)).reduce(
                    (options, key) => {
                        options.push({ name: e.data[key], value: parseInt(key) });
                        return options;
                    },
                    []
                );

                setEffects(options);
            }
        });
    }, []);

    return (
        <div className={classes.root}>
            {[0, 1].map((client, i) => (
                <Box key={i} padding={2}>
                    <Client
                        id={i}
                        socket={socket.current}
                        isConnected={isConnected}
                        effects={effects}
                    />
                </Box>
            ))}
        </div>
    );
};

export default Main;
