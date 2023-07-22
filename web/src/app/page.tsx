import { api } from '@/libs/api'
import dayjs from 'dayjs'
import Link from 'next/link'
import ptBr from 'dayjs/locale/pt-br'
import ChartTanks from '@/components/ChartTanks'
import { data_multiple } from '@/libs/data'

type SuppliesProps = {
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

type SearchProps = {
  dataInicial: string,
  dataFinal: string
}

dayjs.locale(ptBr)

export default async function Home() {

  // const [supplies, setSupplies] = useState<SuppliesProps[]>([
  //   {
  //     id: 0,
  //     tanque: "",
  //     frentista: "",
  //     placa: "",
  //     motorista: "",
  //     inicio: "",
  //     fim: "",
  //     dreno: 0,
  //     latitude: 0,
  //     longitude: 0,
  //   }
  // ]);

  // async function handleSearch(search: SearchProps) {

  //   const { dataInicial, dataFinal } = search

  //   const response = await api.get('/supplies', {
  //     params: {
  //       dataInicio: dataInicial,
  //       dataFim: dataFinal
  //     }
  //   })

  //   setSupplies(response.data)
  // }

  // useEffect(() => {

  // }, [supplies])

  return (
    <div className='flex flex-col gap-10 p-8'>
      {/* <SidebarSearch
        handleSearch={handleSearch}
      /> */}

      {
        // supplies.map(supply => {
        //   return (
        //     <div key={supply.id}>
        //       <p>{supply.tanque}</p>
        //       <p>{supply.frentista}</p>
        //       <p>{supply.placa}</p>
        //       <p>{supply.motorista}</p>
        //       {/* <p>{dayjs(supply.inicio).format("DD/MM/YYYY[ ]HH:mm:ss")}</p> */}


        //     </div>
        //   )
        // })
      }

      <ChartTanks
        options={data_multiple.options}
        series={data_multiple.series}
        type="line"
        height={350}
      />

      <Link
        href="/Dashboard"
        className="text-sm"
      >
        Voltar à timeline
      </Link>
    </div>
  )
}
