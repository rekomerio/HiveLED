import React, { useEffect, useState, useRef } from "react";
import Paper from "@material-ui/core/Paper";
import Box from "@material-ui/core/Box";
import Slider from "@material-ui/core/Slider";
import { Button, Collapse, Typography } from "@material-ui/core";
import { params, getDefaultValues, ParamValue } from "../helpers/parameters";
import { constructMessage } from "../utils/message";
import { Command, Option } from "../helpers/types";
import SyncWithSelect from "./parameters/SyncWithSelect";
import SelectEffect from "./parameters/SelectEffect";

export interface ClientProps {
  id: number;
  socket: WebSocket;
  isConnected: boolean;
  effects: Option[];
  params: ParamValue;
}

const defaultValues = getDefaultValues();

const Client = (props: ClientProps) => {
  const [isExpanded, setIsExpanded] = useState<boolean>(false);
  const [values, setValues] = useState<ParamValue>(defaultValues);
  const previousValues = useRef<ParamValue>(defaultValues);
  const { isConnected, id, socket, effects } = props;

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
    if (!isConnected) return;

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
  }, [values, isConnected, id, socket]);

  useEffect(() => {
    if (Object.keys(props.params).length) setValues(props.params);
    previousValues.current = props.params;
  }, [props.params]);

  return (
    <Paper>
      <Box padding={2}>
        <Typography variant="h6">Client {id + 1}</Typography>
        <Collapse in={isExpanded}>
          <SelectEffect
            values={values}
            setValues={setValues}
            effects={effects}
          />
          {Object.keys(params).map((key) => (
            <React.Fragment key={key}>
              <Typography gutterBottom>{params[key].name}</Typography>
              <Slider
                onChange={(e, val) =>
                  setValues((state) => ({ ...state, [key]: val as number }))
                }
                step={1}
                value={values[key]}
                min={params[key]?.min ?? 0}
                max={params[key]?.max ?? 255}
                getAriaValueText={(val) => val.toString()}
                valueLabelDisplay="on"
              />
            </React.Fragment>
          ))}
          <SyncWithSelect
            values={values}
            setValues={setValues}
            connectedClients={[0, 1, 2]}
            clientId={id}
          />
        </Collapse>
        <Button
          color="secondary"
          variant="contained"
          onClick={() => setIsExpanded((x) => !x)}
        >
          Open
        </Button>
      </Box>
    </Paper>
  );
};

export default Client;
