import React from 'react'
import ReactDOM from 'react-dom/client'
import Home from './pages/Home'
import './styles/global.css'
import { createServer } from 'miragejs'

createServer({

  routes() {
    this.namespace = "api"

    this.get("/supplies", () => {
      return (
        [
          { id: 1, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" },
          { id: 2, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" },
          { id: 3, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" },
          { id: 4, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" },
          { id: 5, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" },
          { id: 6, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" },
          { id: 7, tank: "Tanque 1", date: "12/12/1998", amount: 2, attendant: "Luis Gustavo de Souza Oliveira", plate: "ABC1234", driver: "Luis Gustavo de Souza Oliveira" }
        ]
      )
    })
  }
})

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <Home />
  </React.StrictMode>,
)
