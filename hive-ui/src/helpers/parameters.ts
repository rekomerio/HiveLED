import { Option, Param, ParamType } from "./types";

export const syncWithOptions: Option[] = [
    { name: "None", value: 255 },
    { name: "Client 1", value: 0 },
    { name: "Client 2", value: 1 },
    { name: "Client 3", value: 2 },
    { name: "Client 4", value: 3 },
    { name: "Client 5", value: 4 },
    { name: "Client 6", value: 5 },
    { name: "Client 7", value: 6 },
    { name: "Client 8", value: 7 },
];

export const params: Param = {
    [ParamType.Hue]: { name: "Hue", min: 0, max: 255, default: 100 },
    [ParamType.Saturation]: { name: "Saturation", min: 0, max: 255, default: 255 },
    [ParamType.Value]: { name: "Value", min: 0, max: 255, default: 255 },
    [ParamType.SpawnRate]: { name: "Spawn rate", min: 0, max: 255, default: 150 },
    [ParamType.Brightness]: { name: "Brightness", min: 0, max: 255, default: 80 },
    [ParamType.ActiveEffect]: { name: "Active effect", min: 0, max: 6, default: 0 },
    [ParamType.NextFrameMs]: { name: "Next frame (ms)", min: 16, max: 255, default: 16 },
    [ParamType.PaletteOffset]: { name: "Palette offset", min: 0, max: 150, default: 0 },
    [ParamType.SyncWithId]: { name: "Sync with id", min: 0, max: 255, default: 255 },
    [ParamType.NumLeds]: { name: "Num leds", min: 72, max: 72, default: 72 },
    [ParamType.HueRotationRate]: { name: "Hue rotation rate", min: 0, max: 255, default: 0 },
    [ParamType.FireCooling]: { name: "Fire cooling rate", min: 20, max: 100, default: 55 },
    [ParamType.FireSparking]: { name: "Fire sparkiness", min: 50, max: 200, default: 120 },
};

export const getDefaultValues = () =>
    Object.keys(params).reduce((acc, curr) => {
        acc[curr] = params[curr].default;
        return acc;
    }, {});

export const sliderParams = [
    ParamType.Brightness,
    ParamType.HueRotationRate,
    ParamType.SpawnRate,
    ParamType.PaletteOffset,
    ParamType.NextFrameMs,
    ParamType.FireCooling,
    ParamType.FireSparking,
];
