import React, { useState, useEffect } from "react";
import { Box, IconButton, makeStyles, Typography } from "@material-ui/core";
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
import useSocket from "../hooks/useSocket";
import { Refresh } from "@material-ui/icons";
import axios from "axios";
import { API_URL, WS_URL } from "../config";

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
    const [palettes, setPalettes] = useState<Option[]>([]);
    const [customParams, setCustomParams] = useState<Param>({});
    const [params, setParams] = useState<ParamValue[]>([{}, {}, {}, {}, {}, {}, {}, {}]);
    const [clients, setClients] = useState<ParamValue>();
    const [isConnected, setIsConnected] = useState<boolean>(false);

    const socket = useSocket(WS_URL);

    socket.onclose = (e) => {
        console.log("disconnected");
        setIsConnected(false);
    };
    socket.onopen = (e) => {
        console.log("connected");
        setIsConnected(true);
    };
    socket.onmessage = (e) => {
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

    const getParams = async () => {
        try {
            const res = await axios.get(`${API_URL}/json/params.json`);
            setCustomParams(res.data);
        } catch (error) {
            console.error(error);
        }
    };

    const getPalettes = async () => {
        try {
            const res = await axios.get(`${API_URL}/json/palettes.json`);
            setPalettes(res.data);
        } catch (error) {
            console.error(error);
        }
    };

    const update = () => {
        getParams();
        getPalettes();
        socket.send(constructMessage(Command.GetClients));
        socket.send(constructMessage(Command.GetEffects));
    };

    useEffect(() => {
        if (isConnected) update();
        document.title = "LED Control - " + (isConnected ? "Connected" : "Disconnected");
    }, [isConnected, socket]);

    return (
        <div className={classes.root}>
            <Box padding={2} display="flex" justifyContent="space-between" alignItems="center">
                <Typography variant="subtitle2" color={isConnected ? "secondary" : "primary"}>
                    {isConnected ? "Connected" : "Disconnected"}
                </Typography>
                <IconButton onClick={update} disabled={!isConnected}>
                    <Refresh />
                </IconButton>
            </Box>
            {[0, 1, 2, 3, 4, 5, 6, 7].map((i) => (
                <Box key={i} paddingX={2} paddingY={1}>
                    <Client
                        id={i}
                        socket={socket}
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
