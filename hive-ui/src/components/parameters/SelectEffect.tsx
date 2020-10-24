import React from "react";
import { createStyles, makeStyles, Theme } from "@material-ui/core/styles";
import InputLabel from "@material-ui/core/InputLabel";
import MenuItem from "@material-ui/core/MenuItem";
import FormControl from "@material-ui/core/FormControl";
import Select from "@material-ui/core/Select";
import { ParamType } from "../../helpers/parameters";
import { Option, ParamPropsBase } from "../../helpers/types";

export interface SelectEffectProps extends ParamPropsBase {
    effects: Option[];
}

const useStyles = makeStyles((theme: Theme) =>
    createStyles({
        formControl: {
            margin: theme.spacing(1),
            minWidth: 120,
        },
        selectEmpty: {
            marginTop: theme.spacing(2),
        },
    })
);

const SelectEffect = (props: SelectEffectProps) => {
    const classes = useStyles();
    const { values, setValues, effects } = props;

    const currentValue = values[ParamType.ActiveEffect];

    const setValue = (value: number) => {
        setValues((state) => ({
            ...state,
            [ParamType.ActiveEffect]: value,
        }));
    };

    return (
        <FormControl className={classes.formControl} fullWidth>
            <InputLabel id="effect-select-label">Active effect</InputLabel>
            <Select
                labelId="effect-select-label"
                id="effect-select"
                value={currentValue}
                onChange={(e) => setValue(parseInt(e.target.value as string))}
            >
                {effects.map((option) => (
                    <MenuItem key={option.value} value={option.value}>
                        {option.name}
                    </MenuItem>
                ))}
            </Select>
        </FormControl>
    );
};

export default SelectEffect;
