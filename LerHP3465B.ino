const int IO = 2;
const int I1I2 = 4;
const int Sign = 6;
volatile int sinal = 0;
volatile long leitura = 0;


void setup() {
  Serial.begin(9600);
  pinMode(I1I2, INPUT); // Pino do Ramp Down.
  pinMode(Sign, INPUT); // Pino do PL (polarity).
  pinMode(IO, INPUT); //Pino Rum UP.
  attachInterrupt(digitalPinToInterrupt(IO), leituraADC, FALLING);
}


void loop() {
  digitalWrite(13, HIGH);
  Serial.println(leitura);
  Serial.println(sinal);
  digitalWrite(13, LOW);
  delay(400);
}


void leituraADC() {
  sinal = digitalRead(Sign);
  leitura = pulseIn (I1I2,LOW,300000);
}
