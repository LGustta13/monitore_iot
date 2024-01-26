import CardSupply from '../../components/CardSupply'
import { useSearchSupplies } from '../../hooks/useSearchSupplies'

import './styles.css'

export default function Listagem() {

    const {supplies} = useSearchSupplies();

    return (
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
    )
}