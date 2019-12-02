#include "LIS3DH.h"
#include <Wire.h>

void LIS3DH_init() {
  LIS3DH_write8(CTRL_REG1, 0x97);
  // High res & BDU enabled
  LIS3DH_write8(CTRL_REG4, 0x88);
  // DRDY on INT1
  LIS3DH_write8(CTRL_REG3, 0x10);
  // enable adcs
  LIS3DH_write8(0x1F, 0x80);
}

void LIS3DH_read(double *x, double *y, double *z) {
  static const double scale = 1.0 / 16.0;//2.0 /32768.0;
  
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

//--------------------------------------

void LIS3DH2_init() {
  LIS3DH2_write8(CTRL_REG1, 0x97);
  // High res & BDU enabled
  LIS3DH2_write8(CTRL_REG4, 0x88);
  // DRDY on INT1
  LIS3DH2_write8(CTRL_REG3, 0x10);
  // enable adcs
  LIS3DH2_write8(0x1F, 0x80);
}

void LIS3DH2_read(double *x, double *y, double *z) {
  static const double scale = 1.0 / 16.0;//2.0 /32768.0;
  
  Wire.beginTransmission(LIS3DH2_ADDRESS);
  Wire.write(0x28 | 0x80);
  Wire.endTransmission();

  Wire.requestFrom(LIS3DH2_ADDRESS, 6);

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

void LIS3DH2_write8(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(LIS3DH2_ADDRESS);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();
}

uint8_t LIS3DH2_read8(uint8_t reg) {
  Wire.beginTransmission(LIS3DH2_ADDRESS);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom(LIS3DH2_ADDRESS, 1);
  return Wire.read();
}

//--------------------------------------

void LIS3DH3_init() {
  LIS3DH3_write8(CTRL_REG1, 0x97);
  // High res & BDU enabled
  LIS3DH3_write8(CTRL_REG4, 0x88);
  // DRDY on INT1
  LIS3DH3_write8(CTRL_REG3, 0x10);
  // enable adcs
  LIS3DH3_write8(0x1F, 0x80);
}

void LIS3DH3_read(double *x, double *y, double *z) {
  static const double scale = 1.0 / 16.0;//2.0 /32768.0;
  
  Wire1.beginTransmission(LIS3DH_ADDRESS);
  Wire1.write(0x28 | 0x80);
  Wire1.endTransmission();

  Wire1.requestFrom(LIS3DH_ADDRESS, 6);

  int16_t tx, ty, tz;

  tx = Wire1.read();
  tx |= ((uint16_t)Wire1.read()) << 8;
  ty = Wire1.read();
  ty |= ((uint16_t)Wire1.read()) << 8;
  tz = Wire1.read();
  tz |= ((uint16_t)Wire1.read()) << 8;

  *x = float(tx) * scale;
  *y = float(ty) * scale;
  *z = float(tz) * scale;
}

void LIS3DH3_write8(uint8_t reg, uint8_t value) {
  Wire1.beginTransmission(LIS3DH_ADDRESS);
  Wire1.write((uint8_t)reg);
  Wire1.write((uint8_t)value);
  Wire1.endTransmission();
}

uint8_t LIS3DH3_read8(uint8_t reg) {
  Wire1.beginTransmission(LIS3DH_ADDRESS);
  Wire1.write((uint8_t)reg);
  Wire1.endTransmission();

  Wire1.requestFrom(LIS3DH_ADDRESS, 1);
  return Wire1.read();
}
