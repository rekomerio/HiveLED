export const rescale = (value: number, oldMax: number, newMax: number) => {
    return Math.floor((value / oldMax) * newMax);
};
