import { createMuiTheme } from "@material-ui/core/styles";

export const darkTheme = createMuiTheme({
  palette: {
    type: "dark",
    primary: {
      main: "#512da8",
    },
    secondary: {
      main: "#1de9b6",
    },
    background: {
      //default: "#1d2636",
      //paper: "#0f1724",
      default: "#0f1724",
      paper: "#1d2636",
    },
  },
});
