export enum Command {
    SetParamValue,
    GetParamValue,
    GetParamName,
    GetClientStatus,
    GetNumParams,
    GetEffects,
    GetParams,
}

export interface Option {
    name: string;
    value: number;
}

export interface ParamPropsBase {
    values: ParamValue;
    setValues: React.Dispatch<React.SetStateAction<ParamValue>>;
}

export interface Param {
    [key: string]: {
        name: string;
        min: number;
        max: number;
        default: number;
    };
}

export interface ParamValue {
    [key: string]: number;
}

export interface MessageKeyValue {
    [key: string]: string;
}

export enum ParamType {
    Hue,
    Saturation,
    Value,
    SpawnRate,
    Brightness,
    ActiveEffect,
    NextFrameMs,
    PaletteOffset,
    SyncWithId,
    NumLeds,
    HueRotationRate,
}
