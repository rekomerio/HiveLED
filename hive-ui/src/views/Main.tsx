import React, { useRef, useState, useEffect } from "react";
import { Box, makeStyles } from "@material-ui/core";
import Client from "../components/Client";
import { Command, Option } from "../helpers/types";
import { constructMessage } from "../utils/message";
import { ParamValue } from "../helpers/parameters";

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
  const [params, setParams] = useState<ParamValue[]>([{}, {}, {}]);
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
      } else if (typeof e.data === "string" && e.data.startsWith("{")) {
        const obj = JSON.parse(e.data);
        const name = Object.keys(obj)[0];
        if (name.includes("params")) {
          console.log("params received", Object.keys(obj)[0].split("@"));
          const clientId = Object.keys(obj)[0].split("@")[1];
          console.log(clientId, obj[Object.keys(obj)[0]]);
          setParams((state) =>
            state.map((param, i) => {
              if (i === +clientId) return obj[Object.keys(obj)[0]];
              return param;
            })
          );
        }
        if (name.includes("effects")) {
          const options = Object.keys(obj.effects).map((key) => {
            return {
              name: obj.effects[key],
              value: +key,
            };
          });
          console.log(options);
          setEffects(options);
        }
      }
      return socket.current.close;
    });
  }, []);

  useEffect(() => {
    if (isConnected) {
      socket.current.send(constructMessage(Command.GetParams));
      socket.current.send(constructMessage(Command.GetEffects));
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
            params={params[i]}
          />
        </Box>
      ))}
    </div>
  );
};

export default Main;
