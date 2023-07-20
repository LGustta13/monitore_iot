import { api } from "@/libs/api";
import dayjs from "dayjs";
import Link from "next/link";
import ChartTanks from "@/components/ChartTanks";
import { data_bar, data_multiple, data_multiple_teste } from "@/libs/data";
import SidebarSearch from "@/components/SidebarSearch";
import { SuppliesProps } from "@/global/types";

export default async function Dashboard() {

  async function handleSearchSupplies() {

  }

  // const response = await api.get('/supplies', {
  //   params: {
  //     dataInicio: "2023-06-26T03:01:38.254Z",
  //     dataFim: "2023-06-31T03:01:38.254Z"
  //   }
  // })
  // const supplies: SuppliesProps[] = response.data

  return (
    <>

      {/* header */}
      <header>

      </header>

      {/* sidebar */}

      <aside>



      </aside>

      {/* Conteudo */}
      <main>
        {/* {
          supplies.map(supply => {
            return (
              <div key={supply.id}>
                <p>{supply.tanque}</p>
                <p>{supply.frentista}</p>
                <p>{supply.placa}</p>
                <p>{supply.motorista}</p>
                <p>{dayjs(supply.inicio).format("DD/MM/YYYY[ ]HH:mm:ss")}</p>

              </div>
            )
          })
        } */}

        <Link
          href="/"
          className="text-sm"
        >
          Voltar à timeline
        </Link>

        <ChartTanks
          options={data_bar.options}
          series={data_bar.series}
          type="bar"
          width="500"
        />

        <ChartTanks
          options={data_multiple_teste.options}
          series={data_multiple_teste.series}
          type="line"
          width="500"
        />
      </main>

      {/* footer */}
      <footer>

      </footer>
    </>


  )
}