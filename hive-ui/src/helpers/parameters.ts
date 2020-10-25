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
    0: { name: "Hue", min: 0, max: 255, default: 100 },
    1: { name: "Saturation", min: 0, max: 255, default: 255 },
    2: { name: "Value", min: 0, max: 255, default: 255 },
    3: { name: "Spawn rate", min: 0, max: 255, default: 150 },
    4: { name: "Brightness", min: 0, max: 255, default: 80 },
    5: { name: "Active effect", min: 0, max: 6, default: 0 },
    6: { name: "Next frame (ms)", min: 16, max: 255, default: 16 },
    7: { name: "Palette position", min: 0, max: 255, default: 0 },
    8: { name: "Palette offset", min: 0, max: 150, default: 0 },
    9: { name: "Sync with id", min: 0, max: 255, default: 255 },
    10: { name: "Num leds", min: 72, max: 72, default: 72 },
};

export const getDefaultValues = () =>
    Object.keys(params).reduce((acc, curr) => {
        acc[curr] = params[curr].default;
        return acc;
    }, {});

export const sliderParams = [
    ParamType.Brightness,
    ParamType.SpawnRate,
    ParamType.PaletteOffset,
    ParamType.NextFrameMs,
];
