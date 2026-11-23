// Rotacao do punho - InMoov i2
// Sequencia de demo com movimento suave (aceleracao e desaceleracao):
//   1. Gira devagar para um lado e para o outro (curso completo)
//   2. "Tchauzinho": oscilacoes curtas e rapidas
//   3. Volta ao centro e espera
//
// Ligacao: sinal no pino 9, VCC na fonte 6 V, GND comum com o Arduino
// AJUSTE AMPLITUDE ao curso real do punho antes de rodar a sequencia toda.

#include <Servo.h>

const int   PINO_SERVO  = 9;
const int   PULSO_MIN   = 500;    // limite do servo (us)
const int   PULSO_MAX   = 2500;   // limite do servo (us)
const float CENTRO      = 90.0;   // posicao neutra (graus)
const float AMPLITUDE   = 60.0;   // quanto gira para cada lado (graus) - comece baixo
const float AMPL_TCHAU  = 20.0;   // amplitude do tchauzinho (graus)

Servo punho;
float posAtual = CENTRO;

// Converte graus (0-180) em pulso, para movimento mais fino que write()
void escrever(float graus) {
  graus = constrain(graus, 0.0, 180.0);
  int us = PULSO_MIN + (int)((PULSO_MAX - PULSO_MIN) * graus / 180.0);
  punho.writeMicroseconds(us);
}

// Move de posAtual ate alvo em duracaoMs, com curva suave (cosseno)
void moverSuave(float alvo, unsigned long duracaoMs) {
  float inicio = posAtual;
  unsigned long t0 = millis();
  while (true) {
    unsigned long t = millis() - t0;
    if (t >= duracaoMs) break;
    float fracao = (float)t / duracaoMs;
    float suave  = (1.0 - cos(fracao * PI)) / 2.0;   // 0 -> 1 com aceleracao suave
    escrever(inicio + (alvo - inicio) * suave);
    delay(10);
  }
  escrever(alvo);
  posAtual = alvo;
}

void setup() {
  punho.attach(PINO_SERVO, PULSO_MIN, PULSO_MAX);
  escrever(CENTRO);
  delay(1000);
}

void loop() {
  // 1. Rotacao completa lenta
  moverSuave(CENTRO - AMPLITUDE, 1500);
  delay(500);
  moverSuave(CENTRO + AMPLITUDE, 2500);
  delay(500);
  moverSuave(CENTRO, 1500);
  delay(800);

  // 2. Tchauzinho
  for (int i = 0; i < 3; i++) {
    moverSuave(CENTRO - AMPL_TCHAU, 300);
    moverSuave(CENTRO + AMPL_TCHAU, 300);
  }
  moverSuave(CENTRO, 300);

  // 3. Pausa no centro
  delay(2000);
}