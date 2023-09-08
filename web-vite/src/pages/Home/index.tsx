import './styles.css'
import Header from '../../components/Header'
import { useEffect, useState } from 'react'
import CardSupply from '../../components/CardSupply'

type SupplyProps = {
  id: number,
  tank: string,
  date: string,
  amount: number,
  attendant: string,
  plate: string,
  driver: string,
}

export default function Home() {

  const [supplies, setSupplies] = useState<SupplyProps[]>([])
  const [activeSideBar, setActiveSideBar] = useState(true)

  function handleActiveSideBar() {
    setActiveSideBar(!activeSideBar)
  }

  async function handleSearchData(initialDate: string, finalDate: string) {
    const response = await fetch("http://localhost:5173/api/supplies")
    const data = await response.json()

    setSupplies(data)
  }

  useEffect(() => {
    handleSearchData()
  }, [])

  return (
    <>
      <Header onSearchData={handleSearchData} onActiveSideBar={handleActiveSideBar} activeSideBar={activeSideBar} />

      <section className='home'>
        <table>
          <thead>
            <tr>
              <th scope='col'>Tanque</th>
              <th scope='col'>Data</th>
              <th scope='col'>Litragem</th>
              <th scope='col'>Frentista</th>
              <th scope='col'>Placa</th>
              <th scope='col'>Motorista</th>
            </tr>
          </thead>
          <tbody>
            {
              supplies.map(supply => {
                return (
                  <CardSupply key={supply.id} supply={supply} />
                )
              })
            }
          </tbody>
        </table>
      </section>
    </>
  )
}