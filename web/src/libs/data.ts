export const data_multiple = {
  series: [
    {
      name: "Income",
      type: "column",
      data: [1.4, 2, 2.5, 1.5, 2.5, 2.8, 3.8, 4.6],
    },
    {
      name: "Cashflow",
      type: "column",
      data: [1.1, 3, 3.1, 4, 4.1, 4.9, 6.5, 8.5],
    },
    {
      name: "Revenue",
      type: "line",
      data: [20, 29, 37, 36, 44, 45, 50, 58],
    },
  ],
  options: {
    chart: {
      height: 350,
      type: "line",
      stacked: false,
    },
    dataLabels: {
      enabled: false,
    },
    stroke: {
      width: [1, 1, 4],
    },
    title: {
      text: "teste (2009 - 2016)",
      align: "left",
      offsetX: 110,
    },
    xaxis: {
      categories: [2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016],
    },
    yaxis: [
      {
        axisTicks: {
          show: true,
        },
        axisBorder: {
          show: true,
          color: "#008FFB",
        },
        labels: {
          style: {
            colors: "#008FFB",
          },
        },
        title: {
          text: "Income (thousand crores)",
          style: {
            color: "#008FFB",
          },
        },
        tooltip: {
          enabled: true,
        },
      },
      {
        seriesName: "Income",
        opposite: true,
        axisTicks: {
          show: true,
        },
        axisBorder: {
          show: true,
          color: "#00E396",
        },
        labels: {
          style: {
            colors: "#00E396",
          },
        },
        title: {
          text: "Operating Cashflow (thousand crores)",
          style: {
            color: "#00E396",
          },
        },
      },
      {
        seriesName: "Revenue",
        opposite: true,
        axisTicks: {
          show: true,
        },
        axisBorder: {
          show: true,
          color: "#FEB019",
        },
        labels: {
          style: {
            colors: "#FEB019",
          },
        },
        title: {
          text: "Revenue (thousand crores)",
          style: {
            color: "#FEB019",
          },
        },
      },
    ],
    tooltip: {
      fixed: {
        enabled: true,
        position: "topLeft", // topRight, topLeft, bottomRight, bottomLeft
        offsetY: 30,
        offsetX: 60,
      },
    },
    legend: {
      horizontalAlign: "left",
      offsetX: 40,
    },
  },
};

export const data_multiple_teste = {
  series: [
    {
      name: "Abastecimentos",
      type: "column",
      data: [600, 0, 0, 0, 0, 0, 400, 0],
    },
    {
      name: "Retiradas",
      type: "column",
      data: [0, 0, 0, 0, 0, 0, 2, 0],
    },
    {
      name: "Entradas ou saídas",
      type: "line",
      data: [1, 0, 0, 0, 0, 0, 2, 0],
    },
  ],
  options: {
    chart: {
      height: 350,
      type: "line",
      stacked: false,
    },
    dataLabels: {
      enabled: false,
    },
    stroke: {
      width: [1, 1, 4],
    },
    title: {
      text: "Extrato",
      align: "center",
      offsetX: 0,
    },
    xaxis: {
      categories: ["06/07", "07/07", "08/07", "09/07", "10/07", "11/07", "12/07", "13/07"],
    },
    yaxis: [
      {
        axisTicks: {
          show: true,
        },
        axisBorder: {
          show: true,
          color: "#008FFB",
        },
        labels: {
          style: {
            colors: "#008FFB",
          },
        },
        title: {
          text: "Abastecimentos no tanque",
          style: {
            color: "#008FFB",
          },
        },
        tooltip: {
          enabled: true,
        },
      },
      {
        seriesName: "Abastecimentos",
        opposite: true,
        axisTicks: {
          show: true,
        },
        axisBorder: {
          show: true,
          color: "#00E396",
        },
        labels: {
          style: {
            colors: "#00E396",
          },
        },
        title: {
          text: "Saídas do tanque",
          style: {
            color: "#00E396",
          },
        },
      },
      {
        seriesName: "Entradas e saídas",
        opposite: true,
        axisTicks: {
          show: true,
        },
        axisBorder: {
          show: true,
          color: "#FEB019",
        },
        labels: {
          style: {
            colors: "#FEB019",
          },
        },
        title: {
          text: "Quantidade de entradas e saídas",
          style: {
            color: "#FEB019",
          },
        },
      },
    ],
    tooltip: {
      fixed: {
        enabled: true,
        position: "topLeft", // topRight, topLeft, bottomRight, bottomLeft
        offsetY: 30,
        offsetX: 60,
      },
    },
    legend: {
      horizontalAlign: "left",
      offsetX: 40,
    },
  },
};

export const data_bar = {
  options: {
    chart: {
      id: "basic-bar"
    },
    xaxis: {
      categories: [1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999]
    }
  },
  series: [
    {
      name: "series-1",
      data: [30, 40, 45, 50, 49, 60, 70, 91, 102]
    }
  ]
};

export const datas_examples = {
  dataInicio: "2023-06-26T03:01:38.254Z",
  dataFim: "2023-06-31T03:01:38.254Z"
}
