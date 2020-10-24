import React from "react";
import Main from "./views/Main";
import { ThemeProvider } from "@material-ui/core/styles";
import { darkTheme } from "./theme/theme";

const App = () => {
  return (
    <ThemeProvider theme={darkTheme}>
      <Main />
    </ThemeProvider>
  );
};

export default App;
