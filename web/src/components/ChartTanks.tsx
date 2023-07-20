'use client'

import Chart from "react-apexcharts";

export default function ChartTanks({ options, series, type, width }: any) {

  return (
    <div>
      <Chart
        options={options}
        series={series}
        type={type}
        width={width}
      >
      </Chart>

    </div>
  );
}