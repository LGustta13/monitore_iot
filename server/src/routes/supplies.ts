import { FastifyInstance } from "fastify"
import { prisma } from "../lib/prisma"
import { preprocess, z } from "zod"

export async function suppliesRoutes(app: FastifyInstance) {

  app.get('/supplies', async (request) => {

    const querySchema = z.object({
      dataInicio: z.string(),
      dataFim: z.string()
    })

    const { dataInicio, dataFim } = querySchema.parse(request.query)

    const supplies = await prisma.supply.findMany({
      where: {
        inicio: {
          lte: new Date(dataFim),
          gte: new Date(dataInicio)
        },
      },

      include: {
        tanque: {
          select: {
            nome: true
          }
        },
        frentista: {
          select: {
            nome: true
          }
        },
        veiculo: {
          select: {
            placa: true
          }
        },
        motorista: {
          select: {
            nome: true
          }
        }
      },

      orderBy: {
        inicio: 'asc'
      }
    })

    console.log(supplies)

    return supplies.map(supply => {
      return {
        tanque: supply.tanque.nome,
        frentista: supply.frentista.nome,
        placa: supply.veiculo.placa,
        motorista: supply.motorista.nome,
        inicio: supply.inicio,
        fim: supply.fim,
        dreno: supply.dreno,
        latitude: supply.latitude,
        longitude: supply.longitude,
      }
    })
  })

  app.post('/supplies', async (request) => {

    const bodySchema = z.object({
      tanqueId: z.number(),
      frentistaRFID: z.number(),
      veiculoRFID: z.number(),
      motoristaRFID: z.number(),
      inicio: z.string(),
      fim: z.string(),
      dreno: z.number(),
      latitude: z.number(),
      longitude: z.number()
    })

    const { tanqueId, frentistaRFID, veiculoRFID, motoristaRFID, inicio, fim, dreno, latitude, longitude } = bodySchema.parse(request.body)

    const frentista = await prisma.attendant.findFirst({
      where: {
        rfid: frentistaRFID
      }
    })

    const motorista = await prisma.driver.findFirst({
      where: {
        rfid: motoristaRFID
      }
    })

    const veiculo = await prisma.vehicle.findFirst({
      where: {
        rfid: veiculoRFID
      }
    })

    const supply = (frentista && veiculo && motorista) ? (
      {
        tanqueId,
        frentistaId: frentista.id,
        veiculoId: veiculo.id,
        motoristaId: motorista.id,
        inicio,
        fim,
        dreno,
        latitude,
        longitude
      }
    ) : (
      {
        tanqueId,
        frentistaId: 0,
        veiculoId: 0,
        motoristaId: 0,
        inicio,
        fim,
        dreno,
        latitude,
        longitude
      }
    )

    await prisma.supply.create({
      data: supply
    })
  })

  app.delete('/supplies', async (request, reply) => {

    const querySchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = querySchema.parse(request.query)

    try {
      await prisma.supply.delete({
        where: {
          id
        }
      })

      return reply.send("removed")

    } catch {
      reply.status(500).send("ID NOT FOUND")
    }
  })
}