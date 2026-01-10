#include <Arduino.h>

// ----- CONFIGURAÇÃO -----
#define PIN_TIP   D7   // pino que ativa o TIP122
#define PIN_ADC   A0   // leitura do LC paralelo

const int N = 256;     // número de amostras
uint16_t bufferADC[N]; // buffer de leitura do LC

// protótipo da sua função
float compute_f0(uint16_t *buf, int len);

// ----------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(PIN_TIP, OUTPUT);
  digitalWrite(PIN_TIP, LOW);
  pinMode(PIN_ADC, INPUT);

  Serial.println("Sistema iniciado.");
}

// ----------------------------------------------------
void exciteLC() {
  // Pulso curto de excitação (65 a 150us funciona na maioria dos L)
  digitalWrite(PIN_TIP, HIGH);
  delayMicroseconds(80);
  digitalWrite(PIN_TIP, LOW);

  // LC agora começa a oscilar livremente
}

// ----------------------------------------------------
void sampleLC() {
  // amostragem imediatamente após excitação
  for (int i = 0; i < N; i++) {
    bufferADC[i] = analogRead(PIN_ADC);
    delayMicroseconds(25);  
    // ajusta se quiser amostrar mais rápido ou mais devagar
  }
}

// ----------------------------------------------------
void loop() {

  // 1. excita o LC
  exciteLC();

  // 2. coleta amostras sincronizadas
  sampleLC();

  // 3. calcula frequência de ressonância
  float f0 = compute_f0(bufferADC, N);

  // 4. mostra resultado
  Serial.print("f0 = ");
  Serial.print(f0);
  Serial.println(" Hz");

  delay(300);  // só pra não lotar o serial monitor
}

// ----------------------------------------------------
// VERSÃO BÁSICA DA SUA compute_f0 (caso queira testar)
// substitua pela sua FFT/método real
float compute_f0(uint16_t *buf, int len) {
  // Aqui você coloca sua FFT ou zero–cross
  // Para teste, só retorno algo baseado no buffer
  long soma = 0;
  for (int i = 0; i < len; i++) soma += buf[i];

  float media = soma / (float)len;

  // Apenas exemplo para provar funcionamento
  return media * 10;  
}
