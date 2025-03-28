#include <Arduino.h>

#define EncoderPinA 18
#define EncoderPinB 21
#define ForwardPin 27
#define BackwardPin 26
#define EnablePin 25
volatile long encoderValue = 0;
long ultimaVolta = 0;
unsigned long lastTime = 0;
unsigned long tempoAmostras = 100; 
double RPM = 0.0;

void updateEncoder()
{
if (digitalRead(EncoderPinA) > digitalRead(EncoderPinB))
encoderValue++;
else
encoderValue--;
}

void setup() {
pinMode(ForwardPin,OUTPUT);
pinMode(BackwardPin,OUTPUT);
pinMode(EnablePin,OUTPUT);
pinMode(EncoderPinA, INPUT);
pinMode(EncoderPinB, INPUT);
attachInterrupt(digitalPinToInterrupt(EncoderPinA), updateEncoder, RISING);
Serial.begin(115200);
}

void loop() {
long voltas = encoderValue/10;

if(millis() - lastTime > tempoAmostras){
  RPM = (double(voltas - ultimaVolta) / double(tempoAmostras)) * 60000.0 ;
  //Serial.println(voltas - ultimaVolta);
  //Serial.println(tempoAmostras);
  //Serial.println(RPM);
  ultimaVolta = voltas;
  lastTime = millis();

}

Serial.print("Voltas: ");
Serial.println(voltas);
Serial.print("RPM: ");
Serial.println(RPM);
delay(500);
}
