import { MessageKeyValue, ParamValue } from "../helpers/types";

export const constructMessage = (
    command: number,
    clientId: number = 0,
    param: number = 0,
    value: number = 0
) => {
    const arr = new Uint8Array(5);
    arr[0] = command;
    arr[1] = clientId;
    arr[2] = param;
    arr[3] = value; // Value byte 0
    arr[4] = value << 8; // Value byte 1

    return new Blob([arr]);
};

export const parseOptions = (obj: object, name: string) =>
    Object.keys(obj[name]).map((key) => {
        return {
            name: obj[name][key],
            value: +key,
        };
    });

export const getName = (obj: object) => {
    return Object.keys(obj)[0];
};

export const parseClientId = (obj: object) => {
    return getName(obj).split("@")[1];
};

export const getObjectContents = (obj: object) => {
    return obj[getName(obj)];
};

export const mapObjectValuesToInt = (obj: MessageKeyValue): ParamValue => {
    const constructed = {};
    for (const key in obj) constructed[key] = parseInt(obj[key]);
    return constructed;
};
