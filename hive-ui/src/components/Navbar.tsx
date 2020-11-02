import React from "react";
import { Box, Typography, IconButton, makeStyles, Paper } from "@material-ui/core";
import RefreshIcon from "@material-ui/icons/Refresh";
import CachedIcon from "@material-ui/icons/Cached";
import CheckIcon from "@material-ui/icons/Check";
import BlockIcon from "@material-ui/icons/Block";

export interface NavbarProps {
    isConnected: boolean;
    update: () => void;
    reconnect: () => void;
}

const useStyles = makeStyles((theme) => ({
    typography: {
        marginLeft: theme.spacing(1),
    },
}));

const Navbar = (props: NavbarProps) => {
    const classes = useStyles();
    const { isConnected, update, reconnect } = props;
    const StatusIcon = isConnected ? CheckIcon : BlockIcon;

    return (
        <Paper>
            <Box padding={1} display="flex" justifyContent="space-between" alignItems="center">
                <Box
                    display="flex"
                    justifyContent="space-between"
                    alignItems="center"
                    marginLeft={1}
                >
                    <StatusIcon color={isConnected ? "secondary" : "primary"} />
                    <Typography
                        className={classes.typography}
                        variant="subtitle1"
                        color={isConnected ? "secondary" : "primary"}
                    >
                        {isConnected ? "Connected" : "Disconnected"}
                    </Typography>
                </Box>
                <div>
                    <IconButton onClick={update} disabled={!isConnected}>
                        <RefreshIcon />
                    </IconButton>
                    <IconButton onClick={reconnect} disabled={isConnected}>
                        <CachedIcon />
                    </IconButton>
                </div>
            </Box>
        </Paper>
    );
};

export default Navbar;
