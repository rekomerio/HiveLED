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
import { trimString } from "../../utils/common";

export interface GeneralSelectProps extends ParamPropsBase {
    options: Option[];
    label: string;
    paramType: ParamType;
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

const GeneralSelect = (props: GeneralSelectProps) => {
    const classes = useStyles();
    const { values, setValues, options, label, paramType } = props;

    const currentValue = values[paramType];

    const setValue = (value: number) => {
        setValues((state) => ({
            ...state,
            [paramType]: value,
        }));
    };

    return (
        <div>
            <FormControl className={classes.formControl} fullWidth>
                <InputLabel id={`general-select-label-${paramType}`}>{label}</InputLabel>
                <Select
                    labelId={`general-select-label-${paramType}`}
                    id={`general-select-${paramType}`}
                    value={currentValue}
                    onChange={(e) => setValue(parseInt(e.target.value as string))}
                >
                    {options.map((option) => (
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
                    {trimString(options[currentValue - 1]?.name, 15) ?? "None"}
                </Button>
                <Button
                    size="small"
                    color="secondary"
                    fullWidth
                    onClick={() => setValue(currentValue + 1)}
                    disabled={currentValue >= options.length - 1}
                    endIcon={<NavigateNextIcon />}
                >
                    {trimString(options[currentValue + 1]?.name, 15) ?? "None"}
                </Button>
            </Box>
        </div>
    );
};

export default GeneralSelect;
