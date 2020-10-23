export const constructMessage = (
  command: number,
  clientId: number,
  param: number,
  value: number
) => {
  const arr = new Uint8Array(6);
  arr[0] = command; // Command
  arr[1] = clientId; // Client id
  arr[2] = param; // Param
  arr[3] = value; // Value 0
  arr[4] = 0; // Value 1

  return new Blob([arr]);
};
