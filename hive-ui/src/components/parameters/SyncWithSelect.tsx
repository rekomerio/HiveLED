import React, { useEffect } from "react";
import { createStyles, makeStyles, Theme } from "@material-ui/core/styles";
import InputLabel from "@material-ui/core/InputLabel";
import MenuItem from "@material-ui/core/MenuItem";
import FormControl from "@material-ui/core/FormControl";
import Select from "@material-ui/core/Select";
import { syncWithOptions } from "../../helpers/parameters";
import { ParamPropsBase, ParamType } from "../../helpers/types";
import Button from "@material-ui/core/Button";
import Box from "@material-ui/core/Box";
import ClearIcon from "@material-ui/icons/Clear";

export interface SyncWithSelectProps extends ParamPropsBase {
    connectedClients: number[];
    clientId: number;
}

const useStyles = makeStyles((theme: Theme) =>
    createStyles({
        formControl: {
            margin: theme.spacing(1),
            minWidth: 180,
        },
        selectEmpty: {
            marginTop: theme.spacing(2),
        },
    })
);

const SyncWithSelect = (props: SyncWithSelectProps) => {
    const classes = useStyles();
    const { values, setValues, connectedClients } = props;

    const currentValue = values[ParamType.SyncWithId];

    const isClientConnected = (clientId: number) => {
        return clientId === 255 || connectedClients.includes(clientId);
    };

    const setValue = (value: number) => {
        setValues((state) => ({
            ...state,
            [ParamType.SyncWithId]: value,
        }));
    };

    useEffect(() => {
        for (const clientId of connectedClients) {
            if (currentValue === clientId && !isClientConnected(clientId)) {
                setValue(255);
                break;
            }
        }
    }, [connectedClients]);

    return (
        <Box display="flex" justifyContent="space-between" alignItems="center">
            <FormControl className={classes.formControl} fullWidth>
                <InputLabel id="sync-with-select-label">Sync with</InputLabel>
                <Select
                    labelId="sync-with-select-label"
                    id="sync-with-select"
                    value={currentValue}
                    onChange={(e) => setValue(parseInt(e.target.value as string))}
                >
                    {syncWithOptions.map((option) => (
                        <MenuItem
                            key={option.value}
                            value={option.value}
                            disabled={
                                option.value === props.clientId ||
                                !isClientConnected(option.value)
                            }
                        >
                            {option.name}
                        </MenuItem>
                    ))}
                </Select>
            </FormControl>
            <div>
                <Button
                    onClick={() => setValue(255)}
                    startIcon={<ClearIcon />}
                    variant="contained"
                    size="small"
                    color="primary"
                >
                    Clear
                </Button>
            </div>
        </Box>
    );
};

export default SyncWithSelect;
