import { FastifyInstance } from 'fastify'
import { preprocess, z } from 'zod'
import { prisma } from '../lib/prisma'

export async function driversRoutes(app: FastifyInstance) {

  app.get('/drivers', async (request, reply) => {

    try {
      const drivers = await prisma.driver.findMany({
        include: {
          veiculo: {
            select: {
              placa: true
            }
          }
        },
        orderBy: {
          cadastro: 'asc'
        }
      })

      reply.status(200).send(
        drivers.map(driver => {
          return {
            id: driver.id,
            name: driver.nome,
            rfid: driver.rfid,
            createdAt: driver.cadastro,
            vehicle: driver.veiculo?.placa
          }
        })
      )

    } catch {
      reply.send("NO DRIVER FOUND")
    }
  })

  app.post('/drivers', async (request, reply) => {

    const bodySchema = z.object({
      nome: z.string(),
      rfid: z.number(),
      ativado: z.coerce.boolean().default(false),
      placa: z.string()
    })

    const { nome, rfid, ativado, placa } = bodySchema.parse(request.body)

    try {
      const veiculo = await prisma.vehicle.findFirst({
        where: {
          placa
        },
      })

      await prisma.driver.create({
        data: {
          nome,
          rfid,
          ativado,
          veiculoId: veiculo?.id
        }
      })

      reply.status(200).send("OK")

    } catch {
      reply.send("NO DRIVER CREATED")
    }
  })

  app.put('/drivers/:id', async (request, reply) => {
    const paramsSchema = z.object({
      id: z.preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    const bodySchema = z.object({
      name: z.string(),
      rfid: z.number(),
      active: z.coerce.boolean().default(false),
      placa: z.string(),
    })

    const { name, rfid, active, placa } = bodySchema.parse(request.body)

    try {
      const veiculo = await prisma.vehicle.findFirst({
        where: {
          placa
        }
      })

      await prisma.driver.findUniqueOrThrow({
        where: {
          id
        }
      })

      await prisma.driver.update({
        where: {
          id
        },
        data: {
          nome: name,
          rfid,
          ativado: active,
          veiculoId: veiculo?.id
        }
      }),

        reply.status(200).send("OK")

    } catch {
      reply.send("DRIVER NOT UPDATED")
    }
  })

  app.delete('/drivers/:id', async (request, reply) => {

    const paramsSchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    try {
      await prisma.driver.delete({
        where: {
          id
        }
      })

      reply.status(200).send("OK")

    } catch {
      reply.send("DRIVER NOT DELETED")
    }
  })
}
