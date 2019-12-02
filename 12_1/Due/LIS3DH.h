#ifndef LIS3DH_H
#define LIS3DH_H

#include "Arduino.h"

#define LIS3DH_ADDRESS 0x18
#define LIS3DH2_ADDRESS 0x19
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25

void LIS3DH_init();
void LIS3DH_read(double*, double*, double*);
void LIS3DH_write8(uint8_t, uint8_t);
uint8_t LIS3DH_read8(uint8_t);

void LIS3DH2_init();
void LIS3DH2_read(double*, double*, double*);
void LIS3DH2_write8(uint8_t, uint8_t);
uint8_t LIS3DH2_read8(uint8_t);

void LIS3DH3_init();
void LIS3DH3_read(double*, double*, double*);
void LIS3DH3_write8(uint8_t, uint8_t);
uint8_t LIS3DH3_read8(uint8_t);

#endif
