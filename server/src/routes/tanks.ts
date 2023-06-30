import { FastifyInstance } from "fastify"
import { prisma } from "../lib/prisma"
import { preprocess, z } from "zod"

export async function tanksRoutes(app: FastifyInstance) {

  app.get("/tanks", async (request, reply) => {

    try {
      const tanques = await prisma.tank.findMany()
      reply.status(200).send(tanques)

    } catch {
      reply.send("NO TANK FOUND")
    }
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

      reply.status(200).send("OK")

    } catch {
      reply.send("NO TANK INSERTED")
    }
  })

  app.put("/tanks/:id", async (request, reply) => {

    const paramsSchema = z.object({
      id: z.preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    const bodySchema = z.object({
      idBody: z.number(),
      nome: z.string()
    })

    const { idBody, nome } = bodySchema.parse(request.body)

    console.log(id)

    try {
      const tanque = await prisma.tank.update({
        where: {
          id
        },
        data: {
          id: idBody,
          nome
        }
      })

      reply.status(200).send(tanque)
    } catch {
      reply.send("TANK NOT UPDATED")
    }
  })

  app.delete("/tanks/:id", async (request, reply) => {

    const paramsSchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    try {
      await prisma.tank.delete({
        where: {
          id
        }
      })

      reply.status(200).send("OK")

    } catch {
      reply.send("TANK NOT DELETED")
    }
  })
}