import { useEffect, useRef, useCallback } from "react";

const useDebounce = () => {
  const timeoutRef = useRef<NodeJS.Timeout>(null);

  const debounce = useCallback(
    (fn: () => void, timeMs: number) => {
      const timeout = () => {
        timeoutRef.current = setTimeout(() => {
          timeoutRef.current = null;
          fn();
        }, timeMs);
      };

      if (timeoutRef.current) {
        clearTimeout(timeoutRef.current);
        timeout();
      } else {
        timeout();
      }
    },
    [timeoutRef]
  );

  useEffect(() => {
    return () => clearTimeout(timeoutRef.current);
  }, [timeoutRef]);

  return debounce;
};

export default useDebounce;
