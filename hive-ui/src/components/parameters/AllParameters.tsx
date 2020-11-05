import React from "react";
import { Typography, Slider, makeStyles } from "@material-ui/core";
import { sliderParams, params } from "../../helpers/parameters";
import SyncWithSelect from "./SyncWithSelect";
import { ParamPropsBase, Option, Param, ParamType } from "../../helpers/types";
import ColorWheel from "./ColorWheel";
import GeneralSelect from "./GeneralSelect";
import AdvancedSettings from "./AdvancedSettings";
import { CustomSlider } from "../interactions/Slider";

export interface AllParametersProps extends ParamPropsBase {
    clientId: number;
    effects: Option[];
    palettes: Option[];
    customParams: Param;
}

const useStyles = makeStyles((theme) => ({
    colorWheel: {
        margin: theme.spacing(2),
    },
}));

const AllParameters = (props: AllParametersProps) => {
    const classes = useStyles();
    const { clientId, values, setValues, effects, palettes, customParams } = props;

    const getActiveEffect = () => {
        return effects[values[ParamType.ActiveEffect]];
    };

    const isParamVisible = (key: string) => {
        return customParams[key].effects.includes(getActiveEffect()?.name);
    };

    return (
        <div>
            <GeneralSelect
                label="Select effect"
                values={values}
                setValues={setValues}
                options={effects}
                paramType={ParamType.ActiveEffect}
            />
            <ColorWheel values={values} setValues={setValues} className={classes.colorWheel} />
            {sliderParams.map((key) => (
                <React.Fragment key={key}>
                    <Typography variant="subtitle2">{params[key].name}</Typography>
                    <CustomSlider
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
            {Object.keys(customParams)
                .filter(isParamVisible)
                .map((key) => (
                    <React.Fragment key={key}>
                        <Typography variant="subtitle2">{customParams[key].name}</Typography>
                        <CustomSlider
                            onChange={(e, val) =>
                                setValues((state) => ({ ...state, [key]: val as number }))
                            }
                            step={1}
                            value={values[key]}
                            min={customParams[key]?.min ?? 0}
                            max={customParams[key]?.max ?? 255}
                            getAriaValueText={(val) => val.toString()}
                            valueLabelDisplay="auto"
                        />
                    </React.Fragment>
                ))}
            {getActiveEffect()?.name === "Color palette" && (
                <GeneralSelect
                    label="Select palette"
                    values={values}
                    setValues={setValues}
                    options={palettes}
                    paramType={ParamType.ActivePalette}
                />
            )}
            <SyncWithSelect
                values={values}
                setValues={setValues}
                connectedClients={[0, 1]}
                clientId={clientId}
            />
            <AdvancedSettings values={values} setValues={setValues} clientId={clientId} />
        </div>
    );
};

export default AllParameters;
