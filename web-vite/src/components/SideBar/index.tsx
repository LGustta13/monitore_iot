
import { FormEvent, useState } from 'react'
import './styles.css'

type ActiveProps = {
  onSearchData: (initialDate: string, finalDate: string) => void
  active: boolean
}

export default function SideBar(props: ActiveProps) {
  const { active, onSearchData } = props
  const [initialDate, setInitialDate] = useState('')
  const [finalDate, setFinalDate] = useState('')

  function handleFormSubmit(e: FormEvent) {
    e.preventDefault()

    onSearchData(initialDate, finalDate)
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
        <button className="btn">Listagem</button>
        <button className="btn">Dashboard</button>
      </div>

    </nav>

  )
}