import { ParamValue } from "./parameters";

export enum Command {
  SetParamValue,
  GetParamValue,
  GetParamName,
  GetClientStatus,
  GetNumParams,
  GetEffects,
  GetParams,
}

export interface Option {
  name: string;
  value: number;
}

export interface ParamPropsBase {
  values: ParamValue;
  setValues: React.Dispatch<React.SetStateAction<ParamValue>>;
}
