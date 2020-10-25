import React, { useEffect, useState, useRef } from "react";
import Paper from "@material-ui/core/Paper";
import Box from "@material-ui/core/Box";
import { Collapse, Fab, Typography } from "@material-ui/core";
import { getDefaultValues } from "../helpers/parameters";
import { constructMessage } from "../utils/message";
import { Command, Option, ParamValue } from "../helpers/types";
import ExpandMoreIcon from "@material-ui/icons/ExpandMore";
import ExpandLessIcon from "@material-ui/icons/ExpandLess";
import AllParameters from "./parameters/AllParameters";
import AdvancedSettings from "./parameters/AdvancedSettings";
import useThrottling from "../hooks/useThrottling";

export interface ClientProps {
    id: number;
    socket: WebSocket;
    isSocketOpen: boolean;
    effects: Option[];
    params: ParamValue;
}

const defaultValues = getDefaultValues();

const Client = (props: ClientProps) => {
    const throttle = useThrottling();
    const [isExpanded, setIsExpanded] = useState<boolean>(false);
    const [values, setValues] = useState<ParamValue>(defaultValues);
    const previousValues = useRef<ParamValue>(defaultValues);
    const { isSocketOpen, id, socket, effects } = props;

    const hasChanged = (key: string) => {
        return previousValues.current[key] !== values[key];
    };

    const setPreviousValue = (key: string) => {
        previousValues.current[key] = values[key];
    };

    const getChangedValuesKeys = () => {
        return Object.keys(values).filter((key) => hasChanged(key));
    };

    useEffect(() => {
        if (!isSocketOpen) return;
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
        if (isSocketOpen) socket.send(constructMessage(Command.GetParams, id));
    }, [isSocketOpen, socket]);

    return (
        <Paper>
            <Box padding={2}>
                <Box display="flex" justifyContent="space-between" alignItems="center">
                    <div>
                        <Typography variant="h6">Client {id + 1}</Typography>
                        <Typography variant="subtitle2">
                            {isSocketOpen ? "Connected" : "Disconnected"}
                        </Typography>
                    </div>
                    <Fab
                        color="secondary"
                        size="small"
                        onClick={() => setIsExpanded((x) => !x)}
                    >
                        {isExpanded ? <ExpandLessIcon /> : <ExpandMoreIcon />}
                    </Fab>
                </Box>
                <Collapse in={isExpanded}>
                    <AllParameters
                        clientId={id}
                        values={values}
                        setValues={setValues}
                        effects={effects}
                    />
                </Collapse>
                <AdvancedSettings values={values} setValues={setValues} />
            </Box>
        </Paper>
    );
};

export default Client;
