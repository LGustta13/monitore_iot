export type SuppliesProps = {
  id: number,
  tanque: string,
  frentista: string,
  placa: string,
  motorista: string,
  inicio: string,
  fim: string,
  dreno: number,
  latitude: number,
  longitude: number,
}

export type SearchSuppliesProps = {
  dataInicial: string,
  dataFinal: string
}