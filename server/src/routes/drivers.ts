import { FastifyInstance } from 'fastify'
import { preprocess, z } from 'zod'
import { prisma } from '../lib/prisma'

export async function driversRoutes(app: FastifyInstance) {

  app.get('/drivers', async () => {
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

    return drivers.map((driver) => {
      return {
        id: driver.id,
        name: driver.nome,
        rfid: driver.rfid,
        createdAt: driver.cadastro,
        vehicle: driver.veiculo
      }
    })
  })

  app.post('/drivers', async (request) => {

    const bodySchema = z.object({
      nome: z.string(),
      rfid: z.number(),
      ativado: z.coerce.boolean().default(false),
      placa: z.string()
    })

    const { nome, rfid, ativado, placa } = bodySchema.parse(request.body)

    const veiculo = await prisma.vehicle.findFirst({
      where: {
        placa
      },
    })

    const driver = (veiculo) ? (
      await prisma.driver.create({
        data: {
          nome,
          rfid,
          ativado,
          veiculoId: veiculo.id
        }
      })
    ) : (
      await prisma.driver.create({
        data: {
          nome,
          rfid,
          ativado,
        }
      })
    )

    return driver
  })

  app.put('/drivers/:id', async (request) => {
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

    const veiculo = await prisma.vehicle.findFirst({
      where: {
        placa
      }
    })

    let driver = await prisma.driver.findUniqueOrThrow({
      where: {
        id
      }
    })

    driver = (veiculo) ? (
      await prisma.driver.update({
        where: {
          id
        },
        data: {
          nome: name,
          rfid,
          ativado: active,
          veiculoId: veiculo.id
        }
      })
    ) : (
      await prisma.driver.update({
        where: {
          id
        },
        data: {
          nome: name,
          rfid,
          ativado: active,
        }
      })
    )

    return driver
  })

  app.delete('/drivers/:id', async (request) => {
    const paramsSchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    await prisma.driver.delete({
      where: {
        id
      }
    })
  })
}
