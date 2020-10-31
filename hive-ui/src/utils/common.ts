export const rescale = (value: number, oldMax: number, newMax: number) => {
    return Math.floor((value / oldMax) * newMax);
};

export const trimString = (str: string, maxLength: number) => {
    if (!str) return str;
    if (str.length > maxLength) return str.slice(0, maxLength - 3) + "...";
    return str;
};
