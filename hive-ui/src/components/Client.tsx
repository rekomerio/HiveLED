import React, { useEffect, useState, useRef } from "react";
import Paper from "@material-ui/core/Paper";
import Box from "@material-ui/core/Box";
import Slider from "@material-ui/core/Slider";
import { Button, Typography } from "@material-ui/core";
import { CirclePicker } from "react-color";

export interface ClientProps {
    id: number;
    socket: WebSocket;
}

const colors = [
    "#f44336",
    "#e91e63",
    "#9c27b0",
    "#673ab7",
    "#3f51b5",
    "#2196f3",
    "#03a9f4",
    "#00bcd4",
    "#009688",
    "#4caf50",
    "#8bc34a",
    "#cddc39",
    "#ffeb3b",
    "#ffc107",
    "#ff9800",
    "#ff5722",
];

const params = {
    0: "HUE",
    1: "SPAWN_RATE",
    2: "BRIGHTNESS",
    3: "ACTIVE_EFFECT",
    4: "NEXT_FRAME_MS",
    5: "PALETTE_POSITION",
    6: "PALETTE_OFFSET",
    7: "SYNC_WITH_ID",
    8: "NUM_LEDS",
};

const defaultValues = Object.keys(params).reduce((acc, curr) => {
    acc[curr] = 0;
    return acc;
}, {});

const Client = (props: ClientProps) => {
    const [isConnected, setIsConnected] = useState<boolean>(false);
    const [values, setValues] = useState(defaultValues);
    const [color, setColor] = useState();
    const handleChange = (color) => setColor(color);

    useEffect(() => {
        const interval = setInterval(() => {
            Object.keys(values).forEach((key) => {
                const arr = new Uint8Array(5);
                arr[0] = 0; // Command
                arr[1] = props.id; // Client id
                arr[2] = parseInt(key); // Param
                arr[3] = values[key]; // Value 0
                arr[4] = 0; // Value 1
                const blob = new Blob([arr]);
                //console.log(arr);
                if (isConnected) props.socket.send(blob);
            });
        }, 50);

        return () => clearInterval(interval);
    }, [values]);

    useEffect(() => {
        console.log(color?.hsv);
        //setValues((state) => ({ ...state, 0: color?.hsv?.h }));
    }, [color]);

    return (
        <Paper>
            <Box padding={2}>
                <Typography variant="h6">Client {props.id}</Typography>
                {Object.keys(params).map((key) => (
                    <React.Fragment key={key}>
                        <Typography id="range-slider" gutterBottom>
                            {params[key]}
                        </Typography>
                        <Slider
                            onChange={(e, val) =>
                                setValues((state) => ({ ...state, [key]: val }))
                            }
                            value={values[key]}
                            step={1}
                            min={0}
                            max={255}
                            defaultValue={255}
                            getAriaValueText={(val) => val.toString()}
                        />
                    </React.Fragment>
                ))}

                <CirclePicker
                    color={color}
                    onChangeComplete={handleChange}
                    colors={colors}
                    circleSize={60}
                    width="100%"
                />
            </Box>
            <Button color="primary" variant="contained">
                Open
            </Button>
        </Paper>
    );
};

export default Client;
