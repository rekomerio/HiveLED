import React, { useRef, useState, useEffect } from "react";
import { Box, makeStyles } from "@material-ui/core";
import Client from "../components/Client";
import { Command, Option } from "../helpers/types";
import { constructMessage } from "../utils/message";

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
  const [params, setParams] = useState<Option[][]>([]);
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
      } else if (
        typeof e.data === "string" &&
        (e.data.startsWith("[") || e.data.startsWith("{"))
      ) {
        const obj = JSON.parse(e.data);
        console.log(obj);
        if (Object.keys(obj)[0].includes("params")) {
          console.log("params received", Object.keys(obj)[0].split("@"));
          const clientId = Object.keys(obj)[0].split("@")[0];
          setParams((state) =>
            state.map((params, i) => {
              if (i === +clientId) return {};
            })
          );
        }
        /*
        const options: Option[] = JSON.parse(e.data).map((x) => {
          return {
            name: x[Object.keys(x)[0]],
            value: parseInt(Object.keys(x)[0]),
          };
        });
*/
        //setEffects(options);
      }
    });
  }, []);

  useEffect(() => {
    if (isConnected) {
      const message = constructMessage(Command.GetParams, 0, 0, 0);
      socket.current.send(message);
    }
  }, [isConnected]);

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
