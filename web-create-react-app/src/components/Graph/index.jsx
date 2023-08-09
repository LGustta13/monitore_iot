import ReactApexChart from "react-apexcharts";

import { api } from "../../services/api";
import { useEffect, useState } from "react";

import { Content } from "./style";

export function Graph(handleSearch) {

    const { chave, dataInicial, dataFinal } = handleSearch;
    const [abastecimentos, setAbastecimentos] = useState([]);
    const [drainValue, setDrainValue] = useState([]);
    const [dataValue, setDataValue] = useState([]);
    const [qdeValue, setQdeValue] = useState([]);
    const [chart, setChart] = useState({
        series: [],
        options: {}
    });

    function transformDataForChart(abastecimentos) {
        const filterAbastecimento = abastecimentos.map(abastecimento => (
            {
                drain_value: abastecimento.drain_value,
                data: new Intl.DateTimeFormat('pt-BR').format(new Date(abastecimento.data))
            }
        ))

        const totalDrainValue = filterAbastecimento.reduce((acc, obj) => {
            let key = obj['data'];
            if (!acc[key]) {
                acc[key] = [];
            }
            acc[key].push(obj.drain_value);
            return acc;
        }, {})

        const newTotalDrainValues = [];
        const newTotalAbastecimentos = [];

        const datas = Object.keys(totalDrainValue);
        datas.forEach((data) => {
            newTotalDrainValues.push(totalDrainValue[data].reduce((acc, cur) => acc + cur, 0))
            newTotalAbastecimentos.push(totalDrainValue[data].length)
        })

        const filterAbastecimentoData = abastecimentos.map(abastecimento => (
            new Intl.DateTimeFormat('pt-BR').format(new Date(abastecimento.data))
        ))

        const newTotalDatas = filterAbastecimentoData.filter((elem, pos, self) => (
            self.indexOf(elem) === pos
        ))

        return [newTotalDrainValues, newTotalDatas, newTotalAbastecimentos];
    }

    async function getAbastecimentos(chave, data_inicial, data_final) {
        const response = await api.get(`/getAbastecimentos?chave=${chave}&data_inicial=${data_inicial}&data_final=${data_final}`);

        setAbastecimentos(response.data);
    }

    useEffect(() => {
        console.log(chave);
        getAbastecimentos(
            chave, dataInicial, dataFinal
        );

        const [drain_value, data_value, qde_value] = transformDataForChart(abastecimentos);
        setDrainValue(drain_value);
        setDataValue(data_value);
        setQdeValue(qde_value);
        setChart({
            series: [{
                name: 'Saídas (Litros p/dia)',
                type: 'column',
                data: drainValue
                // data: [1.4, 2, 2.5, 1.5, 2.5, 2.8, 3.8, 4.6]
            }, {
                name: 'Entradas (Litros p/dia)',
                type: 'column',
                data: drainValue
                // data: [1.1, 3, 3.1, 4, 4.1, 4.9, 6.5, 8.5]
            }, {
                name: 'Total de saída (QTDE)',
                type: 'line',
                data: qdeValue
                // data: [20, 29, 37, 36, 44, 45, 50, 58]
            }],
            options: {
                chart: {
                    height: 350,
                    type: 'line',
                    stacked: false
                },
                dataLabels: {
                    enabled: true
                },
                stroke: {
                    width: [0, 0, 2]
                },
                xaxis: {
                    categories: dataValue
                    // categories: [2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016],
                },
                yaxis: [
                    {
                        axisTicks: {
                            show: true,
                        },
                        axisBorder: {
                            show: true,
                            color: '#008FFB'
                        },
                        labels: {
                            style: {
                                colors: '#008FFB',
                            }
                        },
                        tooltip: {
                            enabled: true
                        }
                    },
                    {
                        seriesName: 'Entradas',
                        opposite: true,
                        axisTicks: {
                            show: true,
                        },
                        axisBorder: {
                            show: true,
                            color: '#00E396'
                        },
                        labels: {
                            style: {
                                colors: '#00E396',
                            }
                        }
                    },
                    {
                        seriesName: 'Total de saída',
                        opposite: true,
                        axisTicks: {
                            show: true,
                        },
                        axisBorder: {
                            show: true,
                            color: '#FEB019'
                        },
                        labels: {
                            style: {
                                colors: '#FEB019',
                            },
                        }
                    },
                ],
                tooltip: {
                    fixed: {
                        enabled: true,
                        position: 'topRight', // topRight, topLeft, bottomRight, bottomLeft
                        offsetY: 30,
                        offsetX: 60
                    },
                },
                legend: {
                    horizontalAlign: 'left',
                    offsetX: 40
                }
            },
        });

    }, [chave, dataInicial, dataFinal])

    // const chart = {

    // };

    return (
        <Content>
            <ReactApexChart
                options={chart.options}
                series={chart.series}
            />
        </Content>

    );
}