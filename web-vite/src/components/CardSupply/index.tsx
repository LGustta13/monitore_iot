import './styles.css'

type SupplyProps = {
  id: number,
  tank: string,
  date: string,
  amount: number,
  attendant: string,
  plate: string,
  driver: string,
}

type CardSupplyProps = {
  supply: SupplyProps
}

export default function CardSupply({ supply }: CardSupplyProps) {

  return (
    <tr key={supply.id}>
      <td>{supply.tank}</td>
      <td>{supply.date}</td>
      <td>{supply.amount}</td>
      <td>{supply.attendant}</td>
      <td>{supply.plate}</td>
      <td>{supply.driver}</td>
    </tr>
  )
}