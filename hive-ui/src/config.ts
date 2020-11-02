export const API_URL =
    process.env.NODE_ENV === "development" ? "http://192.168.1.200" : window.location.origin;
export const WS_URL =
    process.env.NODE_ENV === "development"
        ? "ws://192.168.1.200:81"
        : `ws://${window.location.hostname}:81`;
