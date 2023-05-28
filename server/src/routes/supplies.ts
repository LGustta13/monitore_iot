import { FastifyInstance } from "fastify"
import { prisma } from "../lib/prisma"

export async function suppliesRoutes(app: FastifyInstance) {

  app.get('/supplies', async (request, reply) => {

  })

  app.post('/supplies', async (request, reply) => {

  })

  app.put('/supplies/:id', async (request, reply) => {

  })

  app.delete('/supplies/:id', async (request, reply) => {

  })
}