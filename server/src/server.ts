import fastify from "fastify"
import cors from "@fastify/cors"
import { driversRoutes } from "./routes/drivers"
import { suppliesRoutes } from "./routes/supplies"
import { vehiclesRoutes } from "./routes/vehicles"

const app = fastify()
app.register(cors, {
  origin: true,
})

app.register(driversRoutes)
app.register(vehiclesRoutes)
app.register(suppliesRoutes)

app.listen({
  port: process.env.PORT ? Number(process.env.PORT) : 3333,
  host: process.env.HOST || '0.0.0.0'
}).then(() => {
  console.log("HTTP server running on http://localhost:3333")
})