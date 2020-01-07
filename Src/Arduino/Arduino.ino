#include "control.h"
#include "timing.h"
#define BUZZER 6
#define SERVO 5
#define LED 4
#define PHOTORESISTOR 3
#define BUTTON 2

clock* clk;
rotary* rot;
volatile bool btn = false;

void isr () {
  btn = true;
}

void action() {
  btn = false;
  rot->advance_sen();
  attachInterrupt(digitalPinToInterrupt(BUTTON), isr, RISING);
  while (btn == false) {
    digitalWrite(BUZZER, HIGH);
    delay(5000);
    digitalWrite(BUZZER, LOW);
    delay(5000);
  }
}

void setup() {
// Initialize
  ADCSRA = 0; 
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  Serial.begin(9600);
  rot = new rotary(SERVO, LED, PHOTORESISTOR);
// Get time from serial connection
  unsigned long tm = 0;
  char* tm_ptr = (char*) &tm;
  while (Serial.available() < 4) {};
  *tm_ptr       = Serial.read();
  *(tm_ptr + 1) = Serial.read();
  *(tm_ptr + 2) = Serial.read();
  *(tm_ptr + 3) = Serial.read();
  Serial.end();

//Setup clock and register triggers
  clk = new clock(tm, 2);
  clk->reg_trg(28800000, &action);
  clk->reg_trg(72000000, &action);

}

void loop() {
  clk->run();
}
