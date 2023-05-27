/**
 *
 */

#include "../libs/AtuadorServices/AtuadorServices.h"
#include "../libs/DrexiaServices/DrexiaServices.h"
#include "../libs/IdentificacaoServices/IdentificacaoServices.h"
#include "../libs/RtcServices/RtcServices.h"
#include "../libs/AbastecimentoServices/AbastecimentoServices.h"
#include "../libs/GpsServices/GpsServices.h"
#include "../libs/MicroSdServices/MicroSdServices.h"
#include "../libs/GprsServices/GprsServices.h"

AtuadorServices esp32(13, -1, 4, -1, 32, 33, 27, 26);
RtcServices rtc();
GpsServices gps();
GprsServices sim800L();
MicroSdServices sd(5, "Abastecimentos.txt", "Frentistas.txt", "Veiculos.txt", "Motoristas.txt");

// Thread separada, pois é tarefa do sistema como autor
/* CASO DE USO 6 - ENVIAR ABASTECIMENTO*/
bool sistemaControlarEnviarAbastecimento(GprsServices &sim800L, MicroSdServices &sd)
{
  String abastecimentosJson = sd.getAbastecimento();

  while (!sim800L.conectarNaRede())
  {
  }

  String token = sim800L.getToken();
  bool status_requisicao = sim800L.requisicaoHttp(token, abastecimentosJson);

  while (!sim800L.desconectarGprs())
  {
  }

  return status_requisicao;
}

/* CASO DE USO 5 - ARMAZENAR ABASTECIMENTO*/
bool sistemaControlarArmazenarAbastecimento(MicroSdServices &sd, AbastecimentoServices &abastecimento)
{
  const size_t capacidadeJson = JSON_OBJECT_SIZE(14);
  StaticJsonDocument<capacidadeJson> doc;
  doc["id"] = abastecimento.getIdTanque();
  doc["nome_bomba"] = abastecimento.getNomeTanque();
  doc["latitude"] = abastecimento.getLocalizacaoBomba().getLatitude();
  doc["longitude"] = abastecimento.getLocalizacaoBomba().getLongitude();
  doc["volume_abastecido"] = abastecimento.getVolumeSaida();
  doc["data_inicial"]["dia"] = abastecimento.getDataInicial();
  doc["data_inicial"]["timezone_tipo"] = 3;
  doc["data_inicial"]["timezone"] = "UTC";
  doc["data_final"]["dia"] = abastecimento.getDataFinal();
  doc["data_final"]["timezone_tipo"] = 3;
  doc["data_final"]["timezone"] = "UTC";
  doc["id_frentista"] = abastecimento.getUsuarios().getIdFrentista();
  doc["id_veiculo"] = abastecimento.getUsuarios().getIdVeiculo();
  doc["id_motorista"] = abastecimento.getUsuarios().getIdMotorista();

  String jsonString;
  serializeJson(doc, jsonString);

  bool abastecimento_salvo = sd.setAbastecimento(jsonString);
  return abastecimento_salvo;
}

/* CASO DE USO 4 - FINALIZAR ABASTECIMENTO*/
bool sistemaControlarFimAbastecimento(AtuadorServices &esp32, RtcServices &rtc, GpsServices &gps, AbastecimentoServices &abastecimento)
{
  abastecimento.setDataFinal(rtc.getDataHorario());
  gps.handleLatitudeLongitude();
  abastecimento.setLocalizacaoBomba(gps.getLocalizacao());
  abastecimento.setIdTanque(12);
  abastecimento.setNomeTanque("BOMBA_1");
  esp32.atuarNoBuzzer(50);

  return true;
}

/* CASO DE USO 3 - INICIAR ABASTECIMENTO*/
bool sistemaControlarInicioAbastecimento(AtuadorServices &esp32, MicroSdServices &sd, AbastecimentoServices &abastecimento)
{
  float volume_a_ser_abastecido = sd.volumeParaAbastecer(abastecimento.getUsuarios().getIdVeiculo());
  esp32.atuarNoDisplay("Realize o abastecimento", 0);
  abastecimento.setVolumeSaida(verificarPulsos(esp32, volume_a_ser_abastecido));
  esp32.atuarNoReleDeBloqueioZero(LOW);
  esp32.atuarNoBuzzer(50);

  return true;
}
float verificarPulsos(AtuadorServices &esp32, float volume_a_ser_abastecido)
{
  float volume_abastecido = 0;
  float litros_por_pulso = 0.2;
  int count = 0;
  bool flag_de_parada = false;

  while (volume_abastecido <= volume_a_ser_abastecido)
  {
    if (esp32.receberPulsosDoGatilhoZero() > 0 and !flag_de_parada)
    {
      count++;
      volume_abastecido = float(count) * litros_por_pulso;
      flag_de_parada = true;
    }

    else if (esp32.receberPulsosDoGatilhoZero() == 0 and flag_de_parada)
    {
      flag_de_parada = false;
    }
  }

  return volume_abastecido;
}

/* CASO DE USO 2 - GERAR ABASTECIMENTO*/
AbastecimentoServices sistemaControlarAbastecimento(AtuadorServices &esp32, IdentificacaoServices &identificacao, RtcServices &rtc)
{
  AbastecimentoServices abastecimento();
  abastecimento.setUsuarios(identificacao);

  rtc.handleDataHorarioAbastecimento();
  abastecimento.setDataInicial(rtc.getDataHorario());

  esp32.atuarNoReleDeBloqueioZero(HIGH);
  esp32.acionarBuzzer(50);

  return abastecimento;
}

/* CASO DE USO 1 - ESPERAR IDENTIFICAÇÃO*/
IdentificacaoServices sistemaControlarEsperarIdentificacao(AtuadorServices &esp32)
{
  IdentificacaoServices identificacao();

  byte comando_frentista = 0x00;
  byte comando_veiculo = 0x01;
  byte comando_motorista = 0x02;

  // Tratar a condição de id oscioso
  identificacao.setIdFrentista(verificarUsuario(comando_frentista, AtuadorServices esp32));
  identificacao.setIdVeiculo(verificarUsuario(comando_veiculo, AtuadorServices esp32));
  identificacao.setIdMotorista(verificarUsuario(comando_motorista, AtuadorServices esp32));

  return identificacao;
}
int verificarUsuario(byte comando, AtuadorServices &esp32)
{
  bool motorista_ou_veiculo = false;

  if (comando != 0x00)
  {
    motorista_ou_veiculo = true;
  }

  emitirAudio(comando, AtuadorServices esp32);
  return esperarIdentificacao(motorista_ou_veiculo, AtuadorServices esp32);
}
void emitirAudio(byte comando, AtuadorServices &esp32)
{
  if (comando == 0x00)
  {
    esp32.atuarNoDisplay("Identificar frentista");
    esp23.atuarNoBuzzer(50);
    // Identificar frentista no LCD
  }
  else if (comando == 0x01)
  {
    esp32.atuarNoDisplay("Identificar veiculo");
    esp23.atuarNoBuzzer(50);
    // Identificar veículo no LCD
  }
  else if (comando == 0x02)
  {
    esp32.atuarNoDisplay("Identificar motorista");
    esp23.atuarNoBuzzer(50);
    // Identificar motorista no LCD
  }
}
int esperarIdentificacao(bool motorista_ou_veiculo, AtuadorServices &esp32)
{
  DrexiaServices drexia(25);

  unsigned long contador = 0;
  unsigned long tempo_espera_limite = 10000;
  int id_nao_identificado = 0;
  int id_identificacao_osciosa = 1;

  while (drexia.getIdDoCartao() == id_nao_identificado)
  {

    drexia.getIdDoCartao64bits();

    if (motorista_ou_veiculo)
    {
      contador++;
      if (contador >= tempo_espera_limite)
      {
        return id_identificacao_osciosa;
        esp32.atuarNoBizzer(50);
        // Mostrar no LCD para identificacao osciosa
      }
    }
  }

  return drexia.getIdDoCartao();
}

/* CASO DE USO 0 - INICIAR SISTEMA */
bool sistemaControlarInicializacao(AtuadorServices &esp32, GprsServices &sim800L)
{
  esp32.atuarNoLedVerde(HIGH);
  esp32.atuarNoDisplay("Sistema Iniciado", 0);

  sim800L.inicializarGprs(); // Thread separada
  while (!sim800L.conectarNaRede())
  {
  }

  esp32.atuarNoLedAzul(HIGH);
  return true;
}

void setup()
{
  /* CASO DE USO 0 - INICIAR SISTEMA*/
  bool statusInicializacao = false;
  statusInicializacao = sistemaControlarInicializacao(esp32, sim800L);
}

void loop()
{
  if (statusInicializacao)
  {
    /* CASO DE USO 1 - ESPERAR IDENTIFICAÇÃO*/
    IdentificacaoServices identificacao = sistemaControlarEsperarIdentificacao(esp32);

    /* CASO DE USO 2 - GERAR ABASTECIMENTO*/
    AbastecimentoServices abastecimento = sistemaControlarAbastecimento(esp32, identificacao, rtc);

    /* CASO DE USO 3 - INICIAR ABASTECIMENTO*/
    sistemaControlarInicioAbastecimento(esp32, sd, abastecimento);

    /* CASO DE USO 4 - FINALIZAR ABASTECIMENTO*/
    sistemaControlarFimAbastecimento(esp32, rtc, gps, abastecimento);

    /* CASO DE USO 5 - ARMAZENAR ABASTECIMENTO*/
    sistemaControlarArmazenarAbastecimento(sd, abastecimento);

    /* CASO DE USO 6 - ENVIAR ABASTECIMENTO*/
    sistemaControlarEnviarAbastecimento(sim800L, abastecimento);
  }
}
