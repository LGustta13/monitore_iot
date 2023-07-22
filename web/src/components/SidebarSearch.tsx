'use client'

import { FormEvent } from "react";

type SearchProps = {
  dataInicial: string,
  dataFinal: string
}

type HandleSearchProps = {
  handleSearch: (search: SearchProps) => void
}

export default function SidebarSearch({ handleSearch }: HandleSearchProps) {

  async function handleSearchParameters(event: FormEvent<HTMLFormElement>) {
    event.preventDefault()

    const formData = new FormData(event.currentTarget)

    const [dataInicial, dataFinal] = [formData.get('inicio')?.toString(), formData.get('fim')?.toString()]

    if (dataInicial && dataFinal) {
      handleSearch({
        dataInicial, dataFinal
      })
    }
  }

  return (
    <form onSubmit={handleSearchParameters} className="flex flex-col gap-2">
      <input
        className="bg-gray-200 rounded-sm"
        placeholder="Inicio"
        id="inicio"
        name="inicio"
      />

      <input
        className="bg-gray-200 rounded-sm"
        placeholder="Fim"
        id="fim"
        name="fim"
      />

      <button
        type="submit"
      >
        Consultar
      </button>

    </form>
  );
}