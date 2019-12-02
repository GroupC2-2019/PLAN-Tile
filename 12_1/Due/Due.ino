#include <SPI.h>
#include <Wire.h>

#include <DueTimer.h>
#include <arduinoFFT.h>

#include <FastLED.h>
#define FASTLED_FORCE_SOFTWARE_SPI

#include "LEDMatrix.h"
#include "LIS3DH.h"

#define MAG_OFFSET1 997.66
#define MAG_OFFSET2 990.79
#define MAG_OFFSET3 972.23

void ISR_t1();

LEDMatrix panel1(0), panel2(1), panel3(2);
arduinoFFT FFT = arduinoFFT();

volatile int indicator1, indicator2, indicator3;

void setup() {
  Serial.begin(250000);  
  
  Wire.setClock(400000);
  Wire.begin();

  Wire1.setClock(400000);
  Wire1.begin();
  
  SPI.begin();  
  LIS3DH_init();
  LIS3DH2_init();
  LIS3DH3_init();
  delay(500);

  Timer6.attachInterrupt(ISR_t1);
  //Timer6.start(1000); // Calls every 1ms

  panel1.fill(color{255, 0, 0});
  delay(150); 
  panel2.fill(color{0, 255, 0});
  delay(150); 
  panel3.fill(color{0, 0, 255});
  delay(150);
}

volatile float global_mag = 0;
void ISR_t1() {
  Serial.println(global_mag);
}

#define ARR_SIZE 256
#define PREV_FRAMES 50

double mag_arr1[ARR_SIZE], mag_arr2[ARR_SIZE],mag_arr3[ARR_SIZE], imag[ARR_SIZE];

void loop() {
  double x, y, z;
  double max_mag;
  int i;
  bool hit = true;
  int low_count;
  unsigned long t, tt;
  uint16_t counter = 0, hue;

  double mag1, mag2, mag3;
  
  while(1) {
    t=micros();
    LIS3DH_read(&x, &y, &z);
    mag1 = sqrt(x*x + y*y + z*z);

    LIS3DH2_read(&x, &y, &z);
    mag2 = sqrt(x*x + y*y + z*z);

    LIS3DH3_read(&x, &y, &z);
    mag3 = sqrt(x*x + y*y + z*z);

    Serial.print(mag1);
    Serial.print(", ");
    Serial.print(mag2);
    Serial.print(", ");
    Serial.println(mag3);
  }       
  //acc_avg();    

  while(1) {
    LIS3DH_read(&x, &y, &z);
    mag1 = sqrt(x*x + y*y + z*z) - MAG_OFFSET1;
    for(i = 0; i < PREV_FRAMES; i++) {
      mag_arr1[i] = mag1;
      mag_arr2[i] = mag2;
      mag_arr3[i] = mag3;
    }
  
    do {
        t = micros();
        LIS3DH_read(&x, &y, &z);
        mag1 = sqrt(x*x + y*y + z*z) - MAG_OFFSET1;
  
        LIS3DH2_read(&x, &y, &z);
        mag2 = sqrt(x*x + y*y + z*z) - MAG_OFFSET2;
  
        LIS3DH3_read(&x, &y, &z);
        mag3 = sqrt(x*x + y*y + z*z) - MAG_OFFSET3;
  
        for(i = 0; i < (PREV_FRAMES - 1); i++) {
          mag_arr1[i] = mag_arr1[i + 1];
          mag_arr2[i] = mag_arr2[i + 1];
          mag_arr3[i] = mag_arr3[i + 1];
        }
        mag_arr1[PREV_FRAMES - 1] = mag1;
        mag_arr2[PREV_FRAMES - 1] = mag2;
        mag_arr3[PREV_FRAMES - 1] = mag3;
  
        max_mag = max(max(mag1, mag2), mag3);
        
        while(micros() - t < 1000);
    }while(max_mag < 150);
  
    Serial.println("Trigger!");
    
    for(i = PREV_FRAMES; i < ARR_SIZE; i++) {
      t = micros();
      LIS3DH_read(&x, &y, &z);
      mag1 = sqrt(x*x + y*y + z*z) - MAG_OFFSET1;
  
      LIS3DH2_read(&x, &y, &z);
      mag2 = sqrt(x*x + y*y + z*z) - MAG_OFFSET2;
  
      LIS3DH3_read(&x, &y, &z);
      mag3 = sqrt(x*x + y*y + z*z) - MAG_OFFSET3;
      
      mag_arr1[i] = mag1;
      mag_arr2[i] = mag2;
      mag_arr3[i] = mag3;
      
      while(micros() - t < 1000);
    }
  
    Serial.println("Test");
  
    for(i = 0; i < ARR_SIZE; i++) {
      Serial.print(mag_arr1[i]);
      Serial.print(", ");
      Serial.print(mag_arr2[i]);
      Serial.print(", ");
      Serial.println(mag_arr3[i]);
    }
  
    for(i = 0; i < ARR_SIZE; i++) imag[i] = 0.0;    
    FFT.Windowing(mag_arr1, ARR_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(mag_arr1, imag, ARR_SIZE, FFT_FORWARD);
    FFT.ComplexToMagnitude(mag_arr1, imag, ARR_SIZE);
  
    for(i = 0; i < ARR_SIZE; i++) imag[i] = 0.0;    
    FFT.Windowing(mag_arr2, ARR_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(mag_arr2, imag, ARR_SIZE, FFT_FORWARD);
    FFT.ComplexToMagnitude(mag_arr1, imag, ARR_SIZE);
  
    for(i = 0; i < ARR_SIZE; i++) imag[i] = 0.0;    
    FFT.Windowing(mag_arr3, ARR_SIZE, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(mag_arr3, imag, ARR_SIZE, FFT_FORWARD);
    FFT.ComplexToMagnitude(mag_arr1, imag, ARR_SIZE);
  //
  //  for(i = 0; i < ARR_SIZE/2; i++) {
  //    Serial.print(mag_arr1[i]);
  //    Serial.print(", ");
  //    Serial.print(mag_arr2[i]);
  //    Serial.print(", ");
  //    Serial.println(mag_arr3[i]);
  //  }
    delay(250);
    /*if (Serial.available()){
     
      indicator1=Serial.read();
      indicator2=Serial.read();
      indicator2=Serial.read();
    }
      if(indicator1==1 )//|| indicator2==1 || indicator3==1)
      {
        panel1.draw_arrow(0, color{0,255,0}) ;
      }
  
        while(Serial.available())
        {
          Serial.read();
        }
    
  */
  }
  
  while(1);
}

color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
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
  double x, y, z;
  double mag, global_mag, max_mag;
  int i;
  bool hit = true;
  int low_count, t;
  color c;

  uint16_t counter = 0;
  
  while(1) {
    t = millis();
    LIS3DH_read(&x, &y, &z);
    global_mag = sqrt(x*x + y*y + z*z);
    Serial.println(global_mag);
    mag = (global_mag - 1024) / 1048.0 * 255.0;
    if(mag > 255.0) mag = 255.0;
    else if(mag < 0) mag = 0;
//    c = {uint8_t(mag), 0, uint8_t(mag)};
//    panel1.fill(c);    
    if(mag > 0.1) {
      float hue = float((mag - 0.1) / 0.9) * 360;
      panel1.fill(hsvToRgb(hue, 255, 255));
    } else {
      panel1.fill(color{0, 0, 0});
    }
    
    while(millis() - t < 1);
  }
}

void test2() {
  double x, y, z;
  double mag, global_mag, max_mag;
  int i;
  bool hit = true;
  int low_count;
  unsigned long t, tt;
  uint16_t counter = 0, hue;
  
  while(1) {
    t = millis();
    LIS3DH_read(&x, &y, &z);
    global_mag = sqrt(x*x + y*y + z*z) - MAG_OFFSET1;
    //Serial.println(global_mag);
    mag = global_mag / 1024.0;
    
    if(mag < 0.0) mag = 0.0;    
    
    if(mag > 0.1) {    
      hit = true;
      low_count = 0;
      
      if(mag > max_mag) {
        max_mag = mag;
        hue = float((mag - 0.1) / 0.9) * 250;
        panel1.fill(hsvToRgb(hue, 255, 255));
      }
    } else {
      if(low_count++ > 10) {
        if(hit) {
          tt = millis();
          while(millis() - tt < 1000) {
            LIS3DH_read(&x, &y, &z);
            global_mag = sqrt(x*x + y*y + z*z) - MAG_OFFSET1;
            //Serial.println(global_mag);
          }
        }
        hit = false;
        max_mag = 0.0;    
        panel1.fill(color{0, 0, 0}); 
      }
    }
    while(millis() - t < 2);
  }
}

void acc_avg() {
  int i;
  unsigned long t;
  double x, y, z, mag1, mag2, mag3;
  double mag1_sum = 0, mag2_sum = 0, mag3_sum = 0;
  
  for(i = 0; i < 2000; i++) {
    t = micros();
    
    LIS3DH_read(&x, &y, &z);
    mag1 = sqrt(x*x + y*y + z*z);
  
    LIS3DH2_read(&x, &y, &z);
    mag2 = sqrt(x*x + y*y + z*z);
  
    LIS3DH3_read(&x, &y, &z);
    mag3 = sqrt(x*x + y*y + z*z);

    mag1_sum += mag1 / 2000;
    mag2_sum += mag2 / 2000;
    mag3_sum += mag3 / 2000;
    
    while(micros() - t < 1000);
  }

  Serial.print(mag1_sum);
  Serial.print(", ");
  Serial.print(mag2_sum);
  Serial.print(", ");
  Serial.println(mag3_sum);
}
