#include <SPI.h>
#include <Wire.h>

//#include <SD.h>

//File myFile;

#define LIS3DH_ADDRESS 0x18
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25

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

//  SD.begin(10);
//  myFile = SD.open("data.csv", O_WRITE | O_CREAT);

//  start_frame();
//  for(int i = 0; i < 8; i++) {
//    LED_frame(50, 0, 50);
//  }
//  end_frame();
}

void loop() {
  float x, y, z;
  float mag;
  int i;  
  unsigned long t, tt;
  uint16_t s = millis();

  int c = 0;
  tt = millis();

  //Read and serial print take 1.5ms
  while(1) {
    t = micros();
    LIS3DH_read(&x, &y, &z);
    mag = sqrt(x*x + y*y + z*z);
//    Serial.print((int)x);
//    Serial.print(", ");
//    Serial.print((int)y);
//    Serial.print(", ");
//    Serial.println((int)z);
    Serial.println(mag);

    while((micros() - t) < 2000);
  }

  while(1);
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
