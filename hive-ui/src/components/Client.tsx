import React, { useEffect, useState, useRef } from "react";
import Paper from "@material-ui/core/Paper";
import Box from "@material-ui/core/Box";
import { Collapse, Fab, IconButton, makeStyles, Typography } from "@material-ui/core";
import { getDefaultValues } from "../helpers/parameters";
import { constructMessage } from "../utils/message";
import { Command, Option, ParamValue, Param, ParamType } from "../helpers/types";
import ExpandMoreIcon from "@material-ui/icons/ExpandMore";
import ExpandLessIcon from "@material-ui/icons/ExpandLess";
import AllParameters from "./parameters/AllParameters";
import PowerSettingsNewIcon from "@material-ui/icons/PowerSettingsNew";
import useThrottling from "../hooks/useThrottling";
import RefreshIcon from "@material-ui/icons/Refresh";

export interface ClientProps {
    id: number;
    socket: WebSocket;
    isSocketOpen: boolean;
    isConnected: boolean;
    effects: Option[];
    palettes: Option[];
    params: ParamValue;
    customParams: Param;
}

const useStyles = makeStyles((theme) => ({
    button: {
        marginRight: theme.spacing(2),
    },
}));

const defaultValues = getDefaultValues();

const Client = (props: ClientProps) => {
    const classes = useStyles();
    const throttle = useThrottling();
    const [isExpanded, setIsExpanded] = useState<boolean>(false);
    const [values, setValues] = useState<ParamValue>(defaultValues);
    const previousValues = useRef<ParamValue>(defaultValues);
    const { isConnected, isSocketOpen, id, socket, effects, palettes, customParams } = props;

    const hasChanged = (key: string) => {
        return previousValues.current[key] !== values[key];
    };

    const setPreviousValue = (key: string) => {
        previousValues.current[key] = values[key];
    };

    const getChangedValuesKeys = () => {
        return Object.keys(values).filter((key) => hasChanged(key));
    };

    const setPowerState = (value: number) => {
        setValues((state) => ({ ...state, [ParamType.PowerState]: value }));
    };

    const togglePowerState = () => {
        setPowerState(values[ParamType.PowerState] ? 0 : 1);
    };

    useEffect(() => {
        if (!isSocketOpen || !isConnected) return;
        throttle(() => {
            getChangedValuesKeys().forEach((key) => {
                setPreviousValue(key);
                const message = constructMessage(
                    Command.SetParamValue,
                    id,
                    parseInt(key),
                    values[key]
                );
                socket.send(message);
            });
        }, 20);
    }, [values, isSocketOpen, id, socket]);

    useEffect(() => {
        if (Object.keys(props.params).length) {
            setValues(props.params);
            previousValues.current = props.params;
        }
    }, [props.params]);

    useEffect(() => {
        if (isConnected && isSocketOpen) socket.send(constructMessage(Command.GetParams, id));
    }, [isConnected, isSocketOpen, socket]);

    const update = () => {
        if (isConnected && isSocketOpen) socket.send(constructMessage(Command.GetParams, id));
    };

    return (
        <Paper>
            <Box padding={2}>
                <Box display="flex" justifyContent="space-between" alignItems="center">
                    <div>
                        <Typography variant="h5">Client {id + 1}</Typography>
                        <Typography
                            variant="subtitle2"
                            color={isConnected ? "secondary" : "primary"}
                        >
                            {isConnected ? "Connected" : "Disconnected"}
                        </Typography>
                    </div>
                    <div>
                        <Fab
                            color="secondary"
                            onClick={update}
                            disabled={!isConnected}
                            className={classes.button}
                        >
                            <RefreshIcon />
                        </Fab>
                        <Fab
                            color={values[ParamType.PowerState] ? "secondary" : "primary"}
                            disabled={!isConnected}
                            onClick={togglePowerState}
                            className={classes.button}
                        >
                            <PowerSettingsNewIcon />
                        </Fab>
                        <Fab
                            color="secondary"
                            disabled={!isConnected}
                            onClick={() => setIsExpanded((x) => !x)}
                        >
                            {isExpanded ? <ExpandLessIcon /> : <ExpandMoreIcon />}
                        </Fab>
                    </div>
                </Box>
                <Collapse in={isExpanded}>
                    <AllParameters
                        clientId={id}
                        values={values}
                        setValues={setValues}
                        effects={effects}
                        palettes={palettes}
                        customParams={customParams}
                    />
                </Collapse>
            </Box>
        </Paper>
    );
};

export default Client;
