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

#define MATRIX_SIZE 7
#define BRIGHTNESS 25

struct color{
  uint8_t r, g, b;
};

class led_matrix{
public:
  color rgb[MATRIX_SIZE][MATRIX_SIZE];

  led_matrix() {
    clear_buffer();
  }

  void start_frame() {
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
    SPI.transfer(0x00);
  }

  void end_frame(){
    SPI.transfer(0xFF);
    SPI.transfer(0xFF);
    SPI.transfer(0xFF);
    SPI.transfer(0xFF);
  }

  void LED_frame(color c){
    SPI.transfer(0xE0 & BRIGHTNESS);
    SPI.transfer(c.b);
    SPI.transfer(c.g);
    SPI.transfer(c.r);
  }

  void clear_buffer() {
    uint8_t i, j;
    for(i = 0; i < MATRIX_SIZE; i++) {
      for(j = 0; j < MATRIX_SIZE; j++) {
        rgb[i][j] = color{0, 0, 0};
      }
    }
  }

  void write_buffer() {
    int8_t i, j;
    start_frame();
    for(i = 0; i < MATRIX_SIZE; i++) {
      if(i % 2 == 1) {
        for(j = 0; j < MATRIX_SIZE; j++) {
          LED_frame(rgb[i][j]);
        }
      } else {
        for(j = MATRIX_SIZE - 1; j >= 0; j--) {
          LED_frame(rgb[i][j]);
        }
      }
    }
    end_frame();
  }

  void fill(color c) {
    uint8_t i, j;
    for(i = 0; i < MATRIX_SIZE; i++) {
      for(j = 0; j < MATRIX_SIZE; j++) {
        rgb[i][j] = c;
      }
    }
    write_buffer();
  }

  void arrow_north(color c) {
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

  void arrow_northeast(color c) {
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

  void cross(color c) {
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
  void rotate_buffer(uint8_t dir) {
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
  void draw_arrow(uint8_t dir, color c) {
    if(dir % 2 == 0) {
      arrow_north(c);      
    } else {
      arrow_northeast(c);
    }
    rotate_buffer(dir/2);
    write_buffer();
  }

  void draw_cross(color c) {
    cross(c);
    write_buffer();
  }
};

led_matrix m;

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
  test1();
  //test2();
}

color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return color{r, g, b};
}

void test1() {
  float x, y, z;
  float mag, max_mag;
  int i;
  bool hit = true;
  int low_count, t;
  color c;

  uint16_t counter = 0;
  
  while(1) {
    t = millis();    
    LIS3DH_read(&x, &y, &z);
    mag = (sqrt(x*x + y*y + z*z) - 1024) / 1048.0 * 255.0;
    if(mag > 255.0) mag = 255.0;
    else if(mag < 0) mag = 0;
    c = {uint8_t(mag), 0, uint8_t(mag)};
    m.fill(c);    
    while(millis() - t < 1);
  }
}

void test2() {
  float x, y, z;
  float mag, max_mag;
  int i;
  bool hit = true;
  int low_count, t;

  uint16_t counter = 0, hue;
  
  while(1) {
    t = millis();
    
    LIS3DH_read(&x, &y, &z);
    mag = sqrt(x*x + y*y + z*z) / 1024.0 - 1.0;
    if(mag < 0.0) mag = 0.0;    
    
    if(mag > 0.1) {    
      hit = true;
      low_count = 0;
      
      if(mag > max_mag) {
        max_mag = mag;
        hue = float((mag - 0.1) / 0.9) * 360;
        m.fill(hsvToRgb(hue, 255, 255));
      }
    } else {
      if(low_count++ > 10) {
        if(hit) {
          delay(250);
        }
        hit = false;
        max_mag = 0.0;    
        m.fill(color{0, 0, 0}); 
      }
    }
    while(millis() - t < 1);
  }
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
