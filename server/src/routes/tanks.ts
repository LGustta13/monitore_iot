import { FastifyInstance } from "fastify"
import { prisma } from "../lib/prisma"
import { preprocess, z } from "zod"

export async function tanksRoutes(app: FastifyInstance) {

  app.get("/tanks", async (request, reply) => {

    const tanques = await prisma.tank.findMany()

    reply.status(200).send(tanques)
  })

  app.post("/tanks", async (request, reply) => {

    const bodySchema = z.object({
      id: z.number(),
      nome: z.string(),
    })

    const { id, nome } = bodySchema.parse(request.body)

    try {
      await prisma.tank.create({
        data: {
          id,
          nome,
        }
      })
    } catch {
      reply.status(500).send("NOT INSERTED")
    }

    reply.status(200).send("OK")
  })

  app.delete("/tanks", async (request, reply) => {

    const querySchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = querySchema.parse(request.query)

    try {
      await prisma.tank.delete({
        where: {
          id
        }
      })

      reply.status(200).send("OK")

    } catch {
      reply.status(500).send("NO DATA TO DELETE")
    }
  })
}