import React from "react";
import { createStyles, makeStyles, Theme } from "@material-ui/core/styles";
import InputLabel from "@material-ui/core/InputLabel";
import MenuItem from "@material-ui/core/MenuItem";
import FormControl from "@material-ui/core/FormControl";
import Select from "@material-ui/core/Select";
import { Option, ParamPropsBase, ParamType } from "../../helpers/types";
import Button from "@material-ui/core/Button";
import Box from "@material-ui/core/Box";
import NavigateBeforeIcon from "@material-ui/icons/NavigateBefore";
import NavigateNextIcon from "@material-ui/icons/NavigateNext";

export interface SelectPaletteProps extends ParamPropsBase {
    palettes: Option[];
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

const SelectPalette = (props: SelectPaletteProps) => {
    const classes = useStyles();
    const { values, setValues, palettes } = props;

    const currentValue = values[ParamType.ActivePalette];

    const setValue = (value: number) => {
        setValues((state) => ({
            ...state,
            [ParamType.ActivePalette]: value,
        }));
    };

    console.log(values, currentValue);
    return (
        <div>
            <FormControl className={classes.formControl} fullWidth>
                <InputLabel id="palette-select-label">Active palette</InputLabel>
                <Select
                    labelId="palette-select-label"
                    id="palette-select"
                    value={currentValue}
                    onChange={(e) => setValue(parseInt(e.target.value as string))}
                >
                    {palettes.map((option) => (
                        <MenuItem key={option.value} value={option.value}>
                            {option.name}
                        </MenuItem>
                    ))}
                </Select>
            </FormControl>
            <Box display="flex">
                <Button
                    size="small"
                    color="secondary"
                    fullWidth
                    onClick={() => setValue(currentValue - 1)}
                    disabled={currentValue <= 0}
                    startIcon={<NavigateBeforeIcon />}
                >
                    {palettes[currentValue - 1]?.name ?? "None"}
                </Button>
                <Button
                    size="small"
                    color="secondary"
                    fullWidth
                    onClick={() => setValue(currentValue + 1)}
                    disabled={currentValue >= palettes.length - 1}
                    endIcon={<NavigateNextIcon />}
                >
                    {palettes[currentValue + 1]?.name ?? "None"}
                </Button>
            </Box>
        </div>
    );
};

export default SelectPalette;
