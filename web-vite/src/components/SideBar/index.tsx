
import { FormEvent, useState } from 'react'
import './styles.css'
import { useSearchSupplies } from '../../hooks/useSearchSupplies'
import { useRoutes } from '../../hooks/useRoutes'

type ActiveProps = {
  active: boolean
}

export default function SideBar(props: ActiveProps) {
  const { active } = props
  const [initialDate, setInitialDate] = useState('')
  const [finalDate, setFinalDate] = useState('')

  const {handleSearchDataByDate} = useSearchSupplies();
  const {setRoute} = useRoutes();

  function handleFormSubmit(e: FormEvent) {
    e.preventDefault()

    handleSearchDataByDate(initialDate, finalDate);
    setInitialDate('')
    setFinalDate('')
  }

  return (
    <nav className={`${active ? "active" : ""}`}>
      <form onSubmit={handleFormSubmit} action="#">
        <input
          type="text"
          className="initial-date"
          placeholder='Data inicial'
          value={initialDate}
          onChange={e => setInitialDate(e.target.value)}
        />
        <input
          type="text"
          className="final-date"
          placeholder='Data final'
          value={finalDate}
          onChange={e => setFinalDate(e.target.value)}
        />
        <button type='submit' className='btn'>Consultar</button>
      </form>

      <div className="sidebar-nav">
        <button className="btn" onClick={() => setRoute("/Home")}>Listagem</button>
        <button className="btn" onClick={() => setRoute("/Dash")}>Dashboard</button>
      </div>

    </nav>

  )
}