import React, { useEffect, useRef } from "react";
import ReinventedColorWheel from "reinvented-color-wheel";
import { ParamPropsBase, ParamType } from "../../helpers/types";
import { rescale } from "../../utils/common";

export interface ColorWheelProps extends ParamPropsBase {
    className?: string;
}

const ColorWheel = (props: ColorWheelProps) => {
    const ref = useRef<HTMLDivElement>(null);
    const lastTouch = useRef<number>(0);
    const colorWheel = useRef<ReinventedColorWheel>(null);
    const { values, setValues } = props;

    useEffect(() => {
        if (!ref.current) return;
        colorWheel.current = new ReinventedColorWheel({
            // appendTo is the only required property. specify the parent element of the color wheel.
            appendTo: ref.current,

            // initial color (can be specified in hsv / hsl / rgb / hex)
            hsv: [0, 100, 100],

            wheelReflectsSaturation: true,

            // handler
            onChange: (color) => {
                if (!lastTouch.current) {
                    lastTouch.current = Date.now();
                    return;
                }

                lastTouch.current = Date.now();
                const h = rescale(color.hsv[0], 360, 255);
                const s = rescale(color.hsv[1], 100, 255);
                const v = rescale(color.hsv[2], 100, 255);

                setValues((state) => ({
                    ...state,
                    [ParamType.Hue]: h,
                    [ParamType.Saturation]: s,
                    [ParamType.Value]: v,
                }));
            },
        });

        const setWheelValues = () => {
            colorWheel.current.wheelDiameter = Math.min(
                ref.current.getBoundingClientRect().width,
                500
            );
            colorWheel.current.wheelThickness = (colorWheel.current.wheelDiameter / 500) * 40;
            colorWheel.current.handleDiameter = (colorWheel.current.wheelDiameter / 500) * 40;
            colorWheel.current.redraw();
        };

        setWheelValues();

        const onResize = (e) => {
            setWheelValues();
        };

        window.addEventListener("resize", onResize);
        return () => window.removeEventListener("resize", onResize);
    }, [ref]);

    useEffect(() => {
        if (!colorWheel.current) return;
        if (Date.now() - lastTouch.current < 100) return; // To avoid infinite re-render

        const h = rescale(values[ParamType.Hue], 255, 360);
        const s = rescale(values[ParamType.Saturation], 255, 100);
        const v = rescale(values[ParamType.Value], 255, 100);
        colorWheel.current.hsv = [h, s, v];
    }, [values]);

    return <div className={props.className} ref={ref}></div>;
};

export default ColorWheel;
