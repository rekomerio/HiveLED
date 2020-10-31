import React, { useState } from "react";
import SettingsIcon from "@material-ui/icons/Settings";
import IconButton from "@material-ui/core/IconButton";
import { ParamPropsBase, ParamType } from "../../helpers/types";
import Button from "@material-ui/core/Button";
import Dialog from "@material-ui/core/Dialog";
import DialogActions from "@material-ui/core/DialogActions";
import DialogContent from "@material-ui/core/DialogContent";
import DialogContentText from "@material-ui/core/DialogContentText";
import DialogTitle from "@material-ui/core/DialogTitle";
import useMediaQuery from "@material-ui/core/useMediaQuery";
import { makeStyles, useTheme } from "@material-ui/core/styles";
import { Box, TextField } from "@material-ui/core";
import { Close } from "@material-ui/icons";

export interface AdvancedSettingsProps extends ParamPropsBase {}

const useStyles = makeStyles((theme) => ({
    fields: {
        "& > *": {
            marginTop: theme.spacing(2),
        },
    },
}));

const AdvancedSettings: React.SFC<AdvancedSettingsProps> = (props: AdvancedSettingsProps) => {
    const theme = useTheme();
    const classes = useStyles();
    const [isOpen, setIsOpen] = useState<boolean>(false);

    const fullScreen = useMediaQuery(theme.breakpoints.down("sm"));

    const { values, setValues } = props;

    const handleClickOpen = () => {
        setIsOpen(true);
    };

    const handleClose = () => {
        setIsOpen(false);
    };

    return (
        <React.Fragment>
            <IconButton onClick={() => setIsOpen(true)}>
                <SettingsIcon />
            </IconButton>
            <Dialog
                fullScreen={fullScreen}
                open={isOpen}
                onClose={handleClose}
                aria-labelledby="responsive-dialog-title"
            >
                <Box display="flex" justifyContent="space-between" alignItems="center">
                    <DialogTitle>Advanced settings</DialogTitle>
                    <span>
                        <IconButton onClick={handleClose}>
                            <Close />
                        </IconButton>
                    </span>
                </Box>
                <DialogContent dividers>
                    <div className={classes.fields}>
                        <TextField
                            label="Client nickname"
                            variant="filled"
                            defaultValue="Client"
                            fullWidth
                        />
                        <TextField
                            label="Number of LED's"
                            type="number"
                            variant="filled"
                            defaultValue={values[ParamType.NumLeds]}
                            fullWidth
                        />
                    </div>
                </DialogContent>
                <DialogActions>
                    <Button
                        onClick={handleClose}
                        color="primary"
                        variant="contained"
                        autoFocus
                    >
                        Save
                    </Button>
                </DialogActions>
            </Dialog>
        </React.Fragment>
    );
};

export default AdvancedSettings;
