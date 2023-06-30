import { FastifyInstance } from "fastify"
import { prisma } from "../lib/prisma"
import { preprocess, z } from "zod"

export async function suppliesRoutes(app: FastifyInstance) {

  app.get('/supplies', async (request, reply) => {

    const querySchema = z.object({
      dataInicio: z.string(),
      dataFim: z.string()
    })

    const { dataInicio, dataFim } = querySchema.parse(request.query)

    try {
      const abastecimentos = await prisma.supply.findMany({
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

      reply.status(200).send(
        abastecimentos.map(abastecimento => {
          return {
            tanque: abastecimento.tanque.nome,
            frentista: abastecimento.frentista.nome,
            placa: abastecimento.veiculo.placa,
            motorista: abastecimento.motorista.nome,
            inicio: abastecimento.inicio,
            fim: abastecimento.fim,
            dreno: abastecimento.dreno,
            latitude: abastecimento.latitude,
            longitude: abastecimento.longitude,
          }
        })
      )
    } catch {
      reply.send("NO SUPPLIES FOUND")
    }
  })

  app.post('/supplies', async (request, reply) => {

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

    try {
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

      if (frentista && motorista && veiculo) {

        await prisma.supply.create({
          data: {
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
        })
      }

      reply.status(200).send("OK")

    } catch {
      reply.send("SUPPLY NOT CREATED")
    }

  })

  app.delete('/supplies/:id', async (request, reply) => {

    const paramsSchema = z.object({
      id: preprocess(
        (asNumber) => parseInt(z.string().parse(asNumber)),
        z.number()
      )
    })

    const { id } = paramsSchema.parse(request.params)

    try {
      await prisma.supply.delete({
        where: {
          id
        }
      })

      reply.status(200).send("OK")

    } catch {
      reply.send("SUPPLY NOT DELETED")
    }
  })
}