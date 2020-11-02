import React, { useState, useEffect } from "react";
import { Box, makeStyles } from "@material-ui/core";
import Client from "../components/Client";
import { Command, Option, Param, ParamValue } from "../helpers/types";
import {
    constructMessage,
    getName,
    getObjectContents,
    mapObjectValuesToInt,
    parseClientId,
    parseOptions,
} from "../utils/message";

import axios from "axios";
import { API_URL } from "../config";
import { reconnectSocket, webSocket } from "../utils/websocket";
import Navbar from "../components/Navbar";

export interface MainProps {}

const useStyles = makeStyles((theme) => ({
    root: {
        maxWidth: 450,
        margin: "auto",
        height: "100%",
        minHeight: "100vh",
        backgroundColor: theme.palette.background.default,
    },
}));

const Main = () => {
    const classes = useStyles();
    const [effects, setEffects] = useState<Option[]>([]);
    const [palettes, setPalettes] = useState<Option[]>([]);
    const [customParams, setCustomParams] = useState<Param>({});
    const [params, setParams] = useState<ParamValue[]>([{}, {}, {}, {}, {}, {}, {}, {}]);
    const [clients, setClients] = useState<ParamValue>();
    const [isConnected, setIsConnected] = useState<boolean>(false);

    const setSocketEventListeners = () => {
        webSocket.onclose = (e) => {
            console.log("disconnected");
            setIsConnected(false);
        };
        webSocket.onopen = (e) => {
            console.log("connected");
            setIsConnected(true);
        };
        webSocket.onmessage = (e) => {
            if (typeof e.data === "string" && e.data.startsWith("{")) {
                const obj = JSON.parse(e.data);
                const name = getName(obj);
                if (name.includes("params")) {
                    const clientId = parseClientId(obj);
                    const parsedObject = mapObjectValuesToInt(
                        getObjectContents(obj)
                    ) as ParamValue;
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
                if (name.includes("clients")) {
                    const parsedObject = mapObjectValuesToInt(
                        getObjectContents(obj)
                    ) as ParamValue;
                    setClients(parsedObject);
                }
            }
        };
    };

    const getParams = async () => {
        try {
            const res = await axios.get<Param>(`${API_URL}/json/params.json`);
            setCustomParams(res.data);
        } catch (error) {
            console.error(error);
        }
    };

    const getPalettes = async () => {
        try {
            const res = await axios.get<Option[]>(`${API_URL}/json/palettes.json`);
            setPalettes(res.data);
        } catch (error) {
            console.error(error);
        }
    };

    const reconnect = () => {
        reconnectSocket();
        setSocketEventListeners();
    };

    const update = () => {
        getParams();
        getPalettes();
        webSocket.send(constructMessage(Command.GetClients));
        webSocket.send(constructMessage(Command.GetEffects));
    };

    useEffect(() => {
        if (isConnected) update();
        document.title = "LED Control - " + (isConnected ? "Connected" : "Disconnected");
    }, [isConnected, webSocket]);

    useEffect(setSocketEventListeners, []);

    return (
        <div className={classes.root}>
            <Box paddingX={2} paddingTop={2} paddingBottom={1}>
                <Navbar isConnected={isConnected} update={update} reconnect={reconnect} />
            </Box>
            {[0, 1, 2, 3, 4, 5, 6, 7].map((i) => (
                <Box key={i} paddingX={2} paddingY={1}>
                    <Client
                        id={i}
                        socket={webSocket}
                        isSocketOpen={isConnected}
                        isConnected={isConnected && Boolean(clients?.[i])}
                        effects={effects}
                        palettes={palettes}
                        params={params[i]}
                        customParams={customParams}
                    />
                </Box>
            ))}
        </div>
    );
};

export default Main;
