#ifndef LEDMatrix_H
#define LEDMatrix_H

#include "Arduino.h"
#include <FastLED.h>

#define MATRIX_SIZE 7
#define BRIGHTNESS 31

struct color{
  uint8_t r, g, b;
};

class LEDMatrix{
public:
  CRGB leds[MATRIX_SIZE*MATRIX_SIZE];
  color rgb[MATRIX_SIZE][MATRIX_SIZE];
  CLEDController *controller;

  LEDMatrix(uint8_t no);
  void clear_buffer();
  void write_buffer();
  void fill(color c);
  void arrow_north(color c);
  void arrow_northeast(color c);
  void cross(color c);
  void rotate_buffer(uint8_t dir);
  void draw_arrow(uint8_t dir, color c);
  void draw_cross(color c);
};

#endif
