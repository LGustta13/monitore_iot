import { Content } from "./styles";

import { api } from "../../services/api";
import { useEffect, useState } from "react";

type DateProps = {
    date: string,
    timezone_type: number,
    timezone: string
}

type AbastecimentoProps = {
    drain_value: number,
    final_volume: number | null,
    flg_validado: number | null,
    funcao: string,
    initial_volume: number | null,
    nome: string,
    nome_motorista: string,
    nome_veiculo: string,
    pessoa_apoio: string,
    rfid_motorista: string,
    rfid_veiculo: string,
    tank_id: string,
    tank_name: string,
    tipo_technologia: number
    utc_final_date_time: DateProps,
    utc_initial_date_time: DateProps
}

type searchProps = {
    chave: string,
    dataInicial: string,
    dataFinal: string
}

type handleSearchProps = {
    handleSearch: searchProps
}

export function Dashboard({ handleSearch }: handleSearchProps) {

    const { chave, dataInicial, dataFinal } = handleSearch;
    const [abastecimentos, setAbastecimentos] = useState<AbastecimentoProps[]>([]);

    useEffect(() => {
        getAbastecimentos(
            chave, dataInicial, dataFinal
        );
    }, [chave, dataInicial, dataFinal])

    async function getAbastecimentos(chave: string, data_inicial: string, data_final: string) {
        const response = await api.get(`/getAbastecimentos?chave=${chave}&data_inicial=${data_inicial}&data_final=${data_final}`);

        setAbastecimentos(response.data);
    }

    return (
        <Content>
            <table>
                <thead>
                    {
                        abastecimentos.length !== 0 ? (
                            <tr>
                                <th>Bomba</th>
                                <th>Saída</th>
                                <th>Frentista</th>
                                <th>Motorista</th>
                                <th>Placa</th>
                                <th>Data</th>
                            </tr>
                        ) : (
                            <tr></tr>
                        )
                    }
                </thead>

                <tbody>

                    {
                        abastecimentos.map(abastecimento => (
                            <tr>
                                <td>{abastecimento.tank_name}</td>
                                <td>{abastecimento.drain_value}</td>
                                <td>{abastecimento.nome}</td>
                                <td>{abastecimento.nome_motorista}</td>
                                <td>{abastecimento.nome_veiculo}</td>
                                <td>
                                    {new Intl.DateTimeFormat('pt-BR').format(
                                        new Date(abastecimento.utc_initial_date_time.date)
                                    )}
                                </td>
                            </tr>
                        ))
                    }
                </tbody>
            </table>

        </Content>


    );
}