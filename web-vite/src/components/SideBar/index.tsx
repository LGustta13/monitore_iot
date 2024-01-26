
import { FormEvent, useState } from 'react'
import './styles.css'
import { useSearchSupplies } from '../../hooks/useSearchSupplies'
import { useRoutes } from '../../hooks/useRoutes'

import DatePicker, { registerLocale } from "react-datepicker";
import ptBR from 'date-fns/locale/pt-BR';
import "react-datepicker/dist/react-datepicker.css";

registerLocale('pt-BR', ptBR)

type ActiveProps = {
  active: boolean
}

export default function SideBar(props: ActiveProps) {
  const { active } = props
  const [initialDate, setInitialDate] = useState<Date | null>(null)
  const [finalDate, setFinalDate] = useState<Date | null>(null)

  const { handleSearchDataByDate } = useSearchSupplies();
  const { setRoute } = useRoutes();

  function handleFormSubmit(e: FormEvent) {
    e.preventDefault()

    handleSearchDataByDate(initialDate, finalDate);
  }

  return (
    <nav className={`${active ? "active" : ""}`}>
      <form onSubmit={handleFormSubmit} action="#">
        <DatePicker
          selected={initialDate}
          onChange={(date) => setInitialDate(date)}
          locale="pt-BR"
          placeholderText="Data Inicial"
          withPortal
          isClearable
          dateFormat="Pp"
          showYearDropdown
          yearDropdownItemNumber={5}
          scrollableYearDropdown
          showTimeSelect
          timeFormat="p"
          timeIntervals={15}
          className='datePicker'
          clearButtonClassName='clearIcon'
        />
        <DatePicker
          selected={finalDate}
          onChange={(date) => setFinalDate(date)}
          locale="pt-BR"
          placeholderText="Data Final"
          withPortal
          isClearable
          dateFormat="Pp"
          showYearDropdown
          yearDropdownItemNumber={5}
          scrollableYearDropdown
          showTimeSelect
          timeFormat="p"
          timeIntervals={15}
          className='datePicker'
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