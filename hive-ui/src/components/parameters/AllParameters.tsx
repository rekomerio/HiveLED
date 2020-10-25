import React from "react";
import { Typography, Slider, makeStyles } from "@material-ui/core";
import { sliderParams, params } from "../../helpers/parameters";
import SelectEffect from "./SelectEffect";
import SyncWithSelect from "./SyncWithSelect";
import { ParamPropsBase, Option } from "../../helpers/types";
import ColorWheel from "./ColorWheel";

export interface AllParametersProps extends ParamPropsBase {
    clientId: number;
    effects: Option[];
}

const useStyles = makeStyles((theme) => ({
    colorWheel: {
        margin: theme.spacing(2),
    },
}));

const AllParameters = (props: AllParametersProps) => {
    const classes = useStyles();
    const { clientId, values, setValues, effects } = props;

    return (
        <div>
            <SelectEffect values={values} setValues={setValues} effects={effects} />
            <ColorWheel values={values} setValues={setValues} className={classes.colorWheel} />
            {sliderParams.map((key) => (
                <React.Fragment key={key}>
                    <Typography variant="subtitle2">{params[key].name}</Typography>
                    <Slider
                        onChange={(e, val) =>
                            setValues((state) => ({ ...state, [key]: val as number }))
                        }
                        step={1}
                        value={values[key]}
                        min={params[key]?.min ?? 0}
                        max={params[key]?.max ?? 255}
                        getAriaValueText={(val) => val.toString()}
                        valueLabelDisplay="auto"
                    />
                </React.Fragment>
            ))}
            <SyncWithSelect
                values={values}
                setValues={setValues}
                connectedClients={[0, 1]}
                clientId={clientId}
            />
        </div>
    );
};

export default AllParameters;
