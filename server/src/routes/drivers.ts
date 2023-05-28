import { FastifyInstance } from 'fastify'
import { z } from 'zod'
import { prisma } from '../lib/prisma'

type driverProps = {
  id: number,
  nome: string,
  rfid: string,
  cadastro: Date,
  veiculo: {}
}

export async function driversRoutes(app: FastifyInstance) {

  app.get('/drivers', async () => {
    const drivers: driverProps[] = await prisma.driver.findMany({
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

    const veiculoId = await prisma.vehicle.findFirst({
      where: {
        placa
      },
    })

    const driver = await prisma.driver.create({
      data: {
        nome,
        rfid,
        ativado,
        veiculoId: veiculoId.id
      }
    })

    return driver
  })

  app.put('/drivers/:id', async () => {

  })

  app.delete('/drivers/:id', async () => {

  })
}
