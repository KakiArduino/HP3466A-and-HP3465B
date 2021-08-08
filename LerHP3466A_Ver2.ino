const int RUE = 2;
const int Ramp = 4;
const int Sign = 6;
volatile int sinal = 0;
volatile long leitura = 0;


void setup() {
  Serial.begin(9600);
  pinMode(Ramp, INPUT); // Pino do Ramp Down.
  pinMode(Sign, INPUT); // Pino do Sinal (+).
  pinMode(RUE, INPUT); //Pino RunUpEnable.
  attachInterrupt(digitalPinToInterrupt(RUE), leituraADC, FALLING);
}


void loop() {
  digitalWrite(13, HIGH);
  Serial.println(leitura);
  Serial.println(sinal);
  digitalWrite(13, LOW);
  delay(400);
}


void leituraADC() {
  leitura = pulseIn (Ramp,LOW,250000);
  sinal = pulseIn (Sign,LOW,5000);
}

