import './styles.css'

type SupplyProps = {
  id: number,
  tank: string,
  date: Date,
  amount: number,
  attendant: string,
  plate: string,
  driver: string,
}

type CardSupplyProps = {
  supply: SupplyProps
}

export default function CardSupply({ supply }: CardSupplyProps) {

  console.log(supply.date)

  return (
    <tr key={supply.id}>
      <td>{supply.tank}</td>
      <td>{new Date(supply.date).toLocaleString('pt-BR')}</td>
      <td>{supply.amount}</td>
      <td>{supply.attendant}</td>
      <td>{supply.plate}</td>
      <td>{supply.driver}</td>
    </tr>
  )
}