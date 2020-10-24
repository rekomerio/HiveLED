export const constructMessage = (
  command: number,
  clientId: number = 0,
  param: number = 0,
  value: number = 0
) => {
  const arr = new Uint8Array(6);
  arr[0] = command; // Command
  arr[1] = clientId; // Client id
  arr[2] = param; // Param
  arr[3] = value; // Value 0
  arr[4] = 0; // Value 1

  return new Blob([arr]);
};
