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
import { useTheme } from "@material-ui/core/styles";
import { TextField } from "@material-ui/core";

export interface AdvancedSettingsProps extends ParamPropsBase {}

const AdvancedSettings: React.SFC<AdvancedSettingsProps> = (props: AdvancedSettingsProps) => {
    const theme = useTheme();
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
                <DialogTitle>Advanced settings</DialogTitle>
                <DialogContent dividers>
                    <TextField
                        label="Number of LED's"
                        type="number"
                        variant="filled"
                        size="small"
                        defaultValue={values[ParamType.NumLeds]}
                    />
                    <TextField
                        label="Client nickname"
                        variant="filled"
                        size="small"
                        defaultValue="Client"
                    />
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
