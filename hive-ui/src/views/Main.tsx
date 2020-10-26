import React, { useState, useEffect } from "react";
import { Box, makeStyles } from "@material-ui/core";
import Client from "../components/Client";
import { Command, Option, ParamValue } from "../helpers/types";
import {
    constructMessage,
    getName,
    getObjectContents,
    mapObjectValuesToInt,
    parseClientId,
    parseOptions,
} from "../utils/message";
import useSocket from "../hooks/useSocket";

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
    const [effects, setEffects] = useState<Option[]>([]);
    const [params, setParams] = useState<ParamValue[]>([{}, {}, {}, {}, {}, {}, {}, {}]);

    const socketFunctions = React.useMemo(
        () => ({
            onOpen: (e) => {
                console.log(e);
            },
            onClose: (e) => {
                console.log(e);
            },
            onMessage: (e) => {
                if (typeof e.data === "string" && e.data.startsWith("{")) {
                    const obj = JSON.parse(e.data);
                    const name = getName(obj);
                    console.log(e.data);
                    if (name.includes("params")) {
                        const clientId = parseClientId(obj);
                        const parsedObject = mapObjectValuesToInt(
                            getObjectContents(obj)
                        ) as ParamValue;
                        console.log(parsedObject);
                        setParams((state) =>
                            state.map((param, i) => {
                                if (i === +clientId) return parsedObject;
                                return param;
                            })
                        );
                    }
                    if (name.includes("effects")) {
                        setEffects(parseOptions(obj, "effects"));
                    }
                }
            },
        }),
        []
    );

    const { socket, isConnected } = useSocket(socketFunctions, "ws://192.168.1.200:81");

    useEffect(() => {
        if (isConnected) socket.send(constructMessage(Command.GetEffects));
    }, [isConnected, socket]);

    return (
        <div className={classes.root}>
            {[0, 1].map((client, i) => (
                <Box key={i} padding={2}>
                    <Client
                        id={i}
                        socket={socket}
                        isSocketOpen={isConnected}
                        effects={effects}
                        params={params[i]}
                    />
                </Box>
            ))}
        </div>
    );
};

export default Main;
