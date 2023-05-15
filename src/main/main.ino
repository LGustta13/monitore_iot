/**
 *
 */

#include <DrexiaServices.h>
#include <IdentificacaoServices.h>
#include <AtuadorServices.h>
#include <RtcServices.h>
#include <I2cServices.h>
#include <AbastecimentoServices.h>
#include <GpsServices.h>

AtuadorServices esp32(13, -1, 4, -1, 32, 33, 27, 26);

void sistemaControlarArmazenarAbastecimento()
{
}

void sistemaControlarFimAbastecimento(RtcServices &rtc, GpsServices &gps, AbastecimentoServices &abastecimento, AtuadorServices &esp32)
{
  abastecimento.setDataFinal(rtc.getDataHorario());
  gps.handleLatitudeLongitude();
  abastecimento.setLocalizacaoBomba(gps.getLocalizacao());
  abastecimento.setIdTanque(12);
  abastecimento.setNomeTanque("BOMBA_1");
  esp32.atuarNoBuzzer(50);
}

void sistemaControlarInicioAbastecimento(AbastecimentoServices &abastecimento, AtuadorServices &esp32, float volume_a_ser_abastecido)
{

  abastecimento.setVolumeSaida(verificarPulsos(esp32, volume_a_ser_abastecido));
  esp32.atuarNoReleDeBloqueioZero(LOW);
  esp32.atuarNoBuzzer(50);
}

float verificarPulsos(AtuadorServices &esp32, float volume_a_ser_abastecido)
{
  float volume_abastecido = 0;
  int count = 0;
  bool flag_de_parada = false;

  while (volume_abastecido <= volume_a_ser_abastecido)
  {
    if (esp32.receberPulsosDoGatilhoZero() > 0 and !flag_de_parada)
    {
      count++;
      volume_abastecido = float(count) * 0.5;
      flag_de_parada = true;
    }

    else if (esp32.receberPulsosDoGatilhoZero() == 0 and flag_de_parada)
    {
      flag_de_parada = false;
    }
  }

  return volume_abastecido;
}

void sistemaControlarAbastecimento(AtuadorServices &esp32)
{
  AbastecimentoServices abastecimento();
  RtcServices rtc();

  abastecimento.setUsuarios(identificacao);
  rtc.handleDataHorarioAbastecimento();
  abastecimento.setDataInicial(rtc.getDataHorario());

  esp32.atuarNoReleDeBloqueioZero(HIGH);
}

void sistemaControlarInicializacao(AtuadorServices &esp32)
{
  esp32.atuarNoLedVerde(HIGH);
}

void sistemaControlarIdentificacao(AtuadorServices &esp32)
{
  IdentificacaoServices identificacao();

  byte comando_frentista = 0x00;
  byte comando_veiculo = 0x01;
  byte comando_motorista = 0x02;

  // Tratar a condição de id oscioso
  identificacao.setIdFrentista(verificarUsuario(comando_frentista, AtuadorServices esp32));
  identificacao.setIdVeiculo(verificarUsuario(comando_veiculo, AtuadorServices esp32));
  identificacao.setIdMotorista(verificarUsuario(comando_motorista, AtuadorServices esp32));
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
    esp23.atuarNoBuzzer(50);
    // Identificar frentista no LCD
  }
  else if (comando == 0x01)
  {
    esp23.atuarNoBuzzer(50);
    // Identificar veículo no LCD
  }
  else if (comando == 0x02)
  {
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

void setup()
{

  /* CASO DE USO 0 - INICIAR SISTEMA*/
  sistemaControlarInicializacao();
}

void loop()
{

  /* CASO DE USO 1 - ESPERAR IDENTIFICAÇÃO*/
  sistemaControlarIdentificacao(esp32);

  /* CASO DE USO 2 - GERAR ABASTECIMENTO*/
  sistemaControlarAbastecimento(rtc, esp32);

  /* CASO DE USO 3 - INICIAR ABASTECIMENTO*/
  sistemaControlarInicioAbastecimento(abastecimento);

  /* CASO DE USO 4 - FINALIZAR ABASTECIMENTO*/
  sistemaControlarFimAbastecimento(rtc, gps, abastecimento, esp32);

  /* CASO DE USO 5 - ARMAZENAR ABASTECIMENTO*/
  sistemaControlarArmazenarAbastecimento(abastecimento);
}
