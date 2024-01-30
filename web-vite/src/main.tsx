import React, { } from 'react'
import ReactDOM from 'react-dom/client'

// Componentes
import Home from './pages/Home'

// Estilos
import './styles/global.css'

// Libs
import { createServer } from 'miragejs'
import { SearchContextProvider } from './hooks/useSearchSupplies'
import { RoutesContextProvider } from './hooks/useRoutes'

type SupplyProps = {
  id: number,
  tank: string,
  date: Date,
  amount: number,
  attendant: string,
  plate: string,
  driver: string,
}

createServer({

  routes() {
    this.namespace = "api";

    let supplies: SupplyProps[] = [];
    const length = 8;

    for (let i = 1; i < length; i++) {
      supplies.push({
        id: i,
        tank: `Tanque ${i}`,
        date: new Date(Math.floor(Math.random() * (Date.now() - 1704100000000 + 1)) + 1704100000000),
        amount: Math.floor(Math.random() * (20 - 1 + 1)) + 1,
        attendant: "Luis Gustavo",
        plate: "ABC1234",
        driver: "Oliveira"
      })
    }

    this.get("/supplies", () => {
      return supplies;
    })

    this.get("/supplies/:initial/:final", (_response, request) => {
      const start = new Date(request.params.initial);
      const end = new Date(request.params.final);

      

      let inDateSupplies: SupplyProps[] = [];

      supplies.map((supply) => {
        console.log(start);
        console.log(end);
        console.log(supply.date);

        if(supply.date >= start && supply.date <= end) {
          inDateSupplies.push(supply);
        }
      })

      return inDateSupplies;
    })
  }
})

ReactDOM.createRoot(document.getElementById('root')!).render(

  <React.StrictMode>
    <RoutesContextProvider>
      <SearchContextProvider>
        <Home />
      </SearchContextProvider>
    </RoutesContextProvider >
  </React.StrictMode>,


)
