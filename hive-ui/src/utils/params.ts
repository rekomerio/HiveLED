export interface Param {
  [key: string]: {
    name: string;
    min: number;
    max: number;
    default: number;
  };
}

export const params: Param = {
  0: { name: "HUE", min: 0, max: 255, default: 100 },
  1: { name: "SPAWN_RATE", min: 0, max: 255, default: 150 },
  2: { name: "BRIGHTNESS", min: 0, max: 255, default: 80 },
  3: { name: "ACTIVE_EFFECT", min: 0, max: 6, default: 0 },
  4: { name: "NEXT_FRAME_MS", min: 16, max: 255, default: 16 },
  5: { name: "PALETTE_POSITION", min: 0, max: 255, default: 0 },
  6: { name: "PALETTE_OFFSET", min: 0, max: 255, default: 0 },
  7: { name: "SYNC_WITH_ID", min: 0, max: 255, default: 255 },
  8: { name: "NUM_LEDS", min: 72, max: 72, default: 72 },
};

export const getDefaultValues = () =>
  Object.keys(params).reduce((acc, curr) => {
    acc[curr] = params[curr].default;
    return acc;
  }, {});
