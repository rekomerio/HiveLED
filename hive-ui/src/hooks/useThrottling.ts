import { useEffect, useRef, useCallback } from "react";

const useThrottling = () => {
    const timeoutRef = useRef<NodeJS.Timeout>(null);
    const lastThrottle = useRef<number>(0);
    const task = useRef<() => void>(null);

    const throttle = useCallback(
        (fn: () => void, timeMs: number) => {
            task.current = fn;

            const run = () => {
                task.current();
                lastThrottle.current = Date.now();
            };

            if (Date.now() - lastThrottle.current > timeMs) {
                run();
                return;
            }

            if (timeoutRef.current) return;

            timeoutRef.current = setTimeout(() => {
                timeoutRef.current = null;
                run();
            }, timeMs);
        },
        [timeoutRef]
    );

    useEffect(() => {
        return () => clearTimeout(timeoutRef.current);
    }, [timeoutRef]);

    return throttle;
};

export default useThrottling;
