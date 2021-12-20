// Crude 50/60Hz detector for Sony PSone screen SCPH-130
// See here: https://immerhax.com/?p=779
// (2021) Martin Hejnfelt (martin@hejnfelt.com)
  
#define FRQ_50_60_OUT (4)
#define LED (13)
#define VSYNC_IN (2)
int ms = 0;
int v;

void detectFrequency() {
  v = digitalRead(VSYNC_IN);
  if(v == HIGH) return;
  // Only deal with LOW -> LOW
  int ms1 = millis();
  if(ms1-ms < 12) {
    return; // "noise"
  } else if(ms1-ms > 18) {
    digitalWrite(FRQ_50_60_OUT, HIGH);
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(FRQ_50_60_OUT, LOW); 
    digitalWrite(LED, LOW);
  }
  ms = ms1;
}

void setup() {
  pinMode(FRQ_50_60_OUT,OUTPUT);
  digitalWrite(FRQ_50_60_OUT, LOW); 
  pinMode(VSYNC_IN, INPUT_PULLUP);
  ms = millis();
  attachInterrupt(digitalPinToInterrupt(VSYNC_IN),detectFrequency,CHANGE);
}

void loop() {
	// empty on purpose
}
