import React, { useEffect, useState, useRef } from "react";
import Paper from "@material-ui/core/Paper";
import Box from "@material-ui/core/Box";
import Slider from "@material-ui/core/Slider";
import { Button, Collapse, Typography } from "@material-ui/core";
import { params, getDefaultValues } from "../utils/params";
import { constructMessage } from "../utils/message";
import { Command } from "../helpers/types";

export interface ClientProps {
  id: number;
  socket: WebSocket;
  isConnected: boolean;
}

const defaultValues = getDefaultValues();

const Client = (props: ClientProps) => {
  const [isExpanded, setIsExpanded] = useState<boolean>(false);
  const [values, setValues] = useState<{ [key: string]: number }>(
    defaultValues
  );
  const previousValues = useRef<{ [key: string]: number }>(defaultValues);
  const { isConnected, id, socket } = props;

  const hasChanged = (key: string) => {
    return previousValues.current[key] !== values[key];
  };

  const setPreviousValue = (key: string) => {
    return (previousValues.current[key] = values[key]);
  };

  const getChangedValuesKeys = () => {
    return Object.keys(values).filter((key) => hasChanged(key));
  };

  useEffect(() => {
    if (!isConnected) return;

    getChangedValuesKeys().forEach((key) => {
      if (+key === 5) return;

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

  return (
    <Paper>
      <Box padding={2}>
        <Typography variant="h6">Client {id}</Typography>
        <Collapse in={isExpanded}>
          {Object.keys(params).map((key) => (
            <React.Fragment key={key}>
              <Typography id="range-slider" gutterBottom>
                {params[key].name}
              </Typography>
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
