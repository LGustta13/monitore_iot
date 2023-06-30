import { FastifyInstance } from 'fastify'
import { preprocess, z } from 'zod'
import { prisma } from '../lib/prisma'

export async function vehiclesRoutes(app: FastifyInstance) {

  app.get('/vehicles', async (request, reply) => {

    try {
      const vehicles = await prisma.vehicle.findMany({
        include: {
          motorista: {
            select: {
              nome: true
            }
          }
        },
        orderBy: {
          cadastro: 'asc'
        }
      })

      reply.status(200).send(
        vehicles.map(vehicle => {
          return {
            id: vehicle.id,
            placa: vehicle.placa,
            rfid: vehicle.rfid,
            createdAt: vehicle.cadastro,
            driver: vehicle.motorista
          }
        })
      )
    } catch {
      reply.send("NO VEHICLES FOUND")
    }
  })

  app.post('/vehicles', async (request, reply) => {

    const bodySchema = z.object({
      placa: z.string(),
      rfid: z.number(),
      limite: z.number(),
      ativado: z.coerce.boolean().default(false),
    })

    const { placa, rfid, limite, ativado } = bodySchema.parse(request.body)

    try {
      const vehicle = await prisma.vehicle.create({
        data: {
          placa,
          rfid,
          ativado,
          limite,
        }
      })

      reply.status(200).send("OK")
    } catch {
      reply.send("NO VEHICLE CREATED")
    }
  })

  app.put('/vehicles/:id', async (request, reply) => {
    const paramsSchema = z.object({
      id: z.preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    const bodySchema = z.object({
      placa: z.string(),
      rfid: z.number(),
      limit: z.number(),
      active: z.coerce.boolean().default(false),
    })

    const { placa, rfid, active, limit } = bodySchema.parse(request.body)

    try {
      await prisma.vehicle.update({
        where: {
          id
        },
        data: {
          placa,
          rfid,
          ativado: active,
          limite: limit
        }
      })

      reply.status(200).send("OK")
    } catch {
      reply.send("VEHICLE NOT UPDATED")
    }

  })

  app.delete('/vehicles/:id', async (request, reply) => {
    const paramsSchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    try {
      await prisma.vehicle.delete({
        where: {
          id
        }
      })

      reply.status(200).send("OK")

    } catch {
      reply.send("VEHICLE NOT DELETED")
    }

  })
}
