import React, { useEffect, useState } from "react";
import SettingsIcon from "@material-ui/icons/Settings";
import IconButton from "@material-ui/core/IconButton";
import { ParamPropsBase, ParamType } from "../../helpers/types";
import Button from "@material-ui/core/Button";
import Dialog from "@material-ui/core/Dialog";
import DialogActions from "@material-ui/core/DialogActions";
import DialogContent from "@material-ui/core/DialogContent";
import DialogTitle from "@material-ui/core/DialogTitle";
import useMediaQuery from "@material-ui/core/useMediaQuery";
import { makeStyles, useTheme } from "@material-ui/core/styles";
import { Box, TextField } from "@material-ui/core";
import { Close } from "@material-ui/icons";
import { useForm, Controller } from "react-hook-form";

export interface AdvancedSettingsProps extends ParamPropsBase {
    clientId: number;
}

const useStyles = makeStyles((theme) => ({
    fields: {
        "& > *": {
            marginTop: theme.spacing(2),
        },
    },
}));

interface FormInput {
    numLeds: number | string;
    nickname: string;
}

const AdvancedSettings = (props: AdvancedSettingsProps) => {
    const theme = useTheme();
    const classes = useStyles();
    const { values, setValues, clientId } = props;
    const defaultValues = { numLeds: values[ParamType.NumLeds], nickname: "Client" };
    const { control, handleSubmit, reset } = useForm<FormInput>({ defaultValues });
    const [isOpen, setIsOpen] = useState<boolean>(false);
    const fullScreen = useMediaQuery(theme.breakpoints.down("sm"));

    const handleClose = () => {
        setIsOpen(false);
    };

    const onSubmit = (data: FormInput) => {
        console.log(data);
        setValues((state) => ({
            ...state,
            [ParamType.NumLeds]:
                typeof data.numLeds === "string" ? parseInt(data.numLeds) : data.numLeds,
        }));

        handleClose();
    };

    useEffect(() => {
        reset(defaultValues);
    }, [values[ParamType.NumLeds]]);

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
                    <form
                        className={classes.fields}
                        onSubmit={handleSubmit(onSubmit)}
                        id={`settings-form-${clientId}`}
                    >
                        <Controller
                            as={TextField}
                            control={control}
                            label="Client nickname"
                            name="nickname"
                            variant="filled"
                            fullWidth
                        />
                        <Controller
                            as={TextField}
                            control={control}
                            label="Number of LED's"
                            name="numLeds"
                            type="number"
                            variant="filled"
                            fullWidth
                        />
                    </form>
                </DialogContent>
                <DialogActions>
                    <Button
                        type="submit"
                        form={`settings-form-${clientId}`}
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
