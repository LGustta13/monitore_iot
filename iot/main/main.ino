/**
 *  Código principal, ou entidade controladora do sistema
 *  Criado por: Luis Gustavo
 *  Data: 14/07/2023
 */

#include "FuelPumpAutomation/src/FuelPumpAutomation.h"

AtuadorServices esp32(14, -1, 13, 33, 27, 26);
RtcServices rtc;
GpsServices gps;
GprsServices sim800L("simplepm.algar.br", "", "", "", "");
MicroSdServices sd(5, "Abastecimentos.txt", "Frentistas.txt", "Veiculos.txt", "Motoristas.txt");
DrexiaServices drexia(25);
PulserServices pulser(0, 0.005, 400, 4, -1);

Abastecimento *abastecimento;
Identificacao *identificacao;

/* CASO DE USO 6 - ENVIAR ABASTECIMENTO*/
bool sistemaControlarEnviarAbastecimento()
{
  String abastecimentosJson = sd.acessarAbastecimentos();

  while (!sim800L.conectarNaRede())
  {
  }

  bool status_requisicao = sim800L.requisicaoHttp(token, abastecimentosJson);

  while (!sim800L.desconectarGprs())
  {
  }

  return true;
}

/* CASO DE USO 5 - ARMAZENAR ABASTECIMENTO*/
bool sistemaControlarArmazenarAbastecimento()
{
  const size_t capacidadeJson = JSON_OBJECT_SIZE(14);
  StaticJsonDocument<capacidadeJson> doc;
  doc["id"] = abastecimento.getIdTanque();
  doc["nome_bomba"] = abastecimento.getNomeTanque();
  doc["latitude"] = abastecimento->getLocalizacaoBomba().getLatitude();
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

  bool abastecimento_salvo = sd.salvarAbastecimento(jsonString);

  return true;
}

/* CASO DE USO 4 - FINALIZAR ABASTECIMENTO*/
bool sistemaControlarFimAbastecimento()
{
  rtc.handleDataHorarioAbastecimento();
  abastecimento.setDataFinal(rtc.getData());
  gps.handleLatitudeLongitude();
  abastecimento.setLocalizacaoBomba(gps.getLocalizacao().getLatitude(), gps.getLocalizacao().getLongitude());
  abastecimento.setIdTanque(12);
  abastecimento.setNomeTanque("BOMBA_1");

  delete abastecimento;
  abastecimento = NULL;

  return true;
}

/* CASO DE USO 3 - INICIAR ABASTECIMENTO*/
bool sistemaControlarInicioAbastecimento()
{
  float volume_a_ser_abastecido = sd.buscarLimiteAbastecimento(abastecimento.getUsuarios().getIdVeiculo());

  esp32.atuarNoDisplay("Realize o", "abastecimento");
  esp32.atuarNoReleDeBloqueioZero(HIGH);

  pulser.setLimiteAbastecimento(volume_a_ser_abastecido);
  pulser.handleContagemPulsos();
  abastecimento.setVolumeSaida(pulser.getExtrato());

  esp32.atuarNoReleDeBloqueioZero(LOW);
  esp32.atuarNoBuzzer(50);

  esp32.atuarNoDisplay("Extrato", String(pulser->getExtrato()));

  return true;
}

/* CASO DE USO 2 - GERAR ABASTECIMENTO*/
bool sistemaControlarAbastecimento()
{
  abastecimento = new Abastecimento();
  abastecimento.setUsuarios(identificacao->getIdFrentista(), identificacao->getIdVeiculo(), identificacao->getIdMotorista());

  rtc.handleDataHorarioAbastecimento();
  abastecimento.setDataInicial(rtc.getData());

  delete identificacao;
  identificacao = NULL;

  return true;
}

/* CASO DE USO 1 - ESPERAR IDENTIFICAÇÃO*/
bool sistemaControlarEsperarIdentificacao()
{
  identificacao = new Identificacao();

  esp32.atuarNoDisplay("Identificar", "Frentista");
  int frentista = drexia.handleCartao64bits();
  identificacao->setIdFrentista(frentista);
  esp32.atuarNoBuzzer(50);

  esp32.atuarNoDisplay("Identificar", "Veiculo");
  int veiculo = drexia.handleCartao64bits();
  identificacao->setIdVeiculo(veiculo);
  esp32.atuarNoBuzzer(50);

  esp32.atuarNoDisplay("Identificar", "Motorista");
  int motorista = drexia.handleCartao64bits();
  identificacao->setIdMotorista(motorista);
  esp32.atuarNoBuzzer(50);

  return true;
}

/* CASO DE USO 0 - INICIAR SISTEMA */
bool sistemaControlarInicializacao()
{
  esp32.atuarNoLedVerde(HIGH);
  esp32.atuarNoDisplay("Sistema", "Iniciado!");
  esp32.atuarNoLedAzul(HIGH);

  return true;
}

void setup()
{
}

void loop()
{
  if (statusInicializacao)
  {
    /* CASO DE USO 1 - ESPERAR IDENTIFICAÇÃO*/
    sistemaControlarEsperarIdentificacao();

    /* CASO DE USO 2 - GERAR ABASTECIMENTO*/
    sistemaControlarAbastecimento();

    /* CASO DE USO 3 - INICIAR ABASTECIMENTO*/
    sistemaControlarInicioAbastecimento();

    /* CASO DE USO 4 - FINALIZAR ABASTECIMENTO*/
    sistemaControlarFimAbastecimento();

    /* CASO DE USO 5 - ARMAZENAR ABASTECIMENTO*/
    sistemaControlarArmazenarAbastecimento();

    /* CASO DE USO 6 - ENVIAR ABASTECIMENTO*/
    sistemaControlarEnviarAbastecimento();
  }
  else
  {
    /* CASO DE USO 0 - INICIAR SISTEMA*/
    statusInicializacao = sistemaControlarInicializacao();
  }
}