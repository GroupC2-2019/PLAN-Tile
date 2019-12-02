#include "LEDMatrix.h"
#include <SPI.h>
#include <FastLED.h>

LEDMatrix::LEDMatrix(uint8_t no) {
  clear_buffer();
  if(no == 0) {
    controller = &FastLED.addLeds<APA102,46,47>(leds, MATRIX_SIZE*MATRIX_SIZE);
  } else if (no == 1) {
    controller = &FastLED.addLeds<APA102,48,49>(leds, MATRIX_SIZE*MATRIX_SIZE);
  } else if(no == 2) {
    controller = &FastLED.addLeds<APA102,50,51>(leds, MATRIX_SIZE*MATRIX_SIZE);
  }
}

void LEDMatrix::clear_buffer() {
  uint8_t i, j;
  for(i = 0; i < MATRIX_SIZE; i++) {
    for(j = 0; j < MATRIX_SIZE; j++) {
      rgb[i][j] = color{0, 0, 0};
    }
  }
}

void LEDMatrix::write_buffer() {
  int8_t i, j, c;
  for(i = 0; i < MATRIX_SIZE; i++) {
    if(i % 2 == 1) {
      for(c = 0, j = 0; j < MATRIX_SIZE; j++, c++) {
        leds[i*MATRIX_SIZE + c].b = rgb[i][j].r;
        leds[i*MATRIX_SIZE + c].g = rgb[i][j].g;
        leds[i*MATRIX_SIZE + c].r = rgb[i][j].b;
      }
    } else {
      for(c = 0, j = MATRIX_SIZE - 1; j >= 0; j--, c++) {
        leds[i*MATRIX_SIZE + c].b = rgb[i][j].r;
        leds[i*MATRIX_SIZE + c].g = rgb[i][j].g;
        leds[i*MATRIX_SIZE + c].r = rgb[i][j].b;
      }
    }
  }
  controller->showLeds(BRIGHTNESS);
}

void LEDMatrix::fill(color c) {
  uint8_t i, j;
  clear_buffer();
  for(i = 0; i < MATRIX_SIZE; i++) {
    for(j = 0; j < MATRIX_SIZE; j++) {
      rgb[i][j] = c;
    }
  }
  write_buffer();
}

void LEDMatrix::arrow_north(color c) {
  clear_buffer();
  rgb[0][3] = c;

  rgb[1][2] = c;
  rgb[1][3] = c;
  rgb[1][4] = c;

  rgb[2][1] = c;
  rgb[2][2] = c;
  rgb[2][3] = c;
  rgb[2][4] = c;
  rgb[2][5] = c;

  rgb[3][2] = c;
  rgb[3][3] = c;
  rgb[3][4] = c;

  rgb[4][2] = c;
  rgb[4][3] = c;
  rgb[4][4] = c;

  rgb[5][2] = c;
  rgb[5][3] = c;
  rgb[5][4] = c;

  rgb[6][2] = c;
  rgb[6][3] = c;
  rgb[6][4] = c;
}

void LEDMatrix::arrow_northeast(color c) {
  clear_buffer();
  rgb[0][3] = c;
  rgb[0][4] = c;
  rgb[0][5] = c;
  rgb[0][6] = c;

  rgb[1][4] = c;
  rgb[1][5] = c;
  rgb[1][6] = c;

  rgb[2][3] = c;
  rgb[2][4] = c;
  rgb[2][5] = c;
  rgb[2][6] = c;

  rgb[3][2] = c;
  rgb[3][3] = c;
  rgb[3][4] = c;
  rgb[3][6] = c;

  rgb[4][1] = c;
  rgb[4][2] = c;
  rgb[4][3] = c;

  rgb[5][0] = c;
  rgb[5][1] = c;
  rgb[5][2] = c;

  rgb[6][0] = c;
  rgb[6][1] = c;
}

void LEDMatrix::cross(color c) {
  clear_buffer();

  rgb[0][0] = c;
  rgb[0][6] = c;

  rgb[1][1] = c;
  rgb[1][5] = c;

  rgb[2][2] = c;
  rgb[2][4] = c;

  rgb[3][3] = c;

  rgb[4][2] = c;
  rgb[4][4] = c;

  rgb[5][1] = c;
  rgb[5][5] = c;

  rgb[6][0] = c;
  rgb[6][6] = c;    
}

// Rotate: 0 = 0 degrees, 1 = 90 degrees, 2 = 180 degrees, 3 = 270 degrees - Clockwise
void LEDMatrix::rotate_buffer(uint8_t dir) {
  if(dir == 0 || dir > 3) {
    return;
  }
  dir = 4-dir;
  int8_t i, j, k;
  for(i = 0; i < MATRIX_SIZE / 2; i++) { 
    for(j = i; j < MATRIX_SIZE-i-1; j++) { 
      for(k = 0; k < dir; k++) {
        color temp = rgb[i][j]; 
        rgb[i][j] = rgb[j][MATRIX_SIZE-1-i]; 
        rgb[j][MATRIX_SIZE-1-i] = rgb[MATRIX_SIZE-1-i][MATRIX_SIZE-1-j]; 
        rgb[MATRIX_SIZE-1-i][MATRIX_SIZE-1-j] = rgb[MATRIX_SIZE-1-j][i];
        rgb[MATRIX_SIZE-1-j][i] = temp; 
      }
    } 
  }
}

//dir = 0 - 7: 0 = 0 degrees, 1 = 45 degrees, ... , 7 = 315 degrees
void LEDMatrix::draw_arrow(uint8_t dir, color c) {
  if(dir % 2 == 0) {
    arrow_north(c);      
  } else {
    arrow_northeast(c);
  }
  rotate_buffer(dir/2);
  write_buffer();
}

void LEDMatrix::draw_cross(color c) {
  cross(c);
  write_buffer();
}
