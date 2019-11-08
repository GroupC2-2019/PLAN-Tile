#include <SPI.h>
#include <Wire.h>


#define LIS3DH_ADDRESS 0x18
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25

int indicator;

void setup() {
  Serial.begin(230400);
  
  Wire.begin();

  // enable all axes, High res 1.3 KHz
  LIS3DH_write8(CTRL_REG1, 0x97);

  // High res & BDU enabled
  LIS3DH_write8(CTRL_REG4, 0x88);

  // DRDY on INT1
  LIS3DH_write8(CTRL_REG3, 0x10);

  // enable adcs
  LIS3DH_write8(0x1F, 0x80);


}

void loop() {
  float x, y, z;
  float mag;
  
  
  int t, tt;
  uint16_t s = millis();

  uint16_t counter = 0;

  tt = millis();
  while(1) {
    t = micros();
    LIS3DH_read(&x, &y, &z);

  Serial.print((int)x);
  Serial.print(", ");
  Serial.print((int)y);
  Serial.print(", ");
  Serial.println((int)z);

  /*
    while((micros() - t) < 750);

    if(millis() - tt > 6000) {
      while(1);
    }*/

  //if (Serial.available() > 0){
     indicator = Serial.read();
     if (indicator == 1){
        digitalWrite(12, HIGH);
        delay(100);
        digitalWrite(12, LOW);
      }
 // }
  }

  while(1);
}

void start_frame() {
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
}

void end_frame(){
  SPI.transfer(255);
  SPI.transfer(255);
  SPI.transfer(255);
  SPI.transfer(255);
}

void LED_frame(uint8_t r, uint8_t g, uint8_t b){
  SPI.transfer(255);
  SPI.transfer(b);
  SPI.transfer(g);
  SPI.transfer(r);
}


void LIS3DH_read(float *x, float *y, float *z) {
  static const float scale = 1.0 / 16.0;//2.0 /32768.0;
  
  Wire.beginTransmission(LIS3DH_ADDRESS);
  Wire.write(0x28 | 0x80);
  Wire.endTransmission();

  Wire.requestFrom(LIS3DH_ADDRESS, 6);

  int16_t tx, ty, tz;

  tx = Wire.read();
  tx |= ((uint16_t)Wire.read()) << 8;
  ty = Wire.read();
  ty |= ((uint16_t)Wire.read()) << 8;
  tz = Wire.read();
  tz |= ((uint16_t)Wire.read()) << 8;

  *x = float(tx) * scale;
  *y = float(ty) * scale;
  *z = float(tz) * scale;
}

void LIS3DH_write8(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(LIS3DH_ADDRESS);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();
}

uint8_t LIS3DH_read8(uint8_t reg) {
  Wire.beginTransmission(LIS3DH_ADDRESS);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom(LIS3DH_ADDRESS, 1);
  return Wire.read();
}
