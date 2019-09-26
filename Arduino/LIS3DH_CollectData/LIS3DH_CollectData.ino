#include <Wire.h>

#define LIS3DH    0x18

uint8_t CTRL_REG1 = 0x20;
uint8_t CTRL_REG2 = 0x21;
uint8_t CTRL_REG3 = 0x22;
uint8_t CTRL_REG4 = 0x23;
uint8_t CTRL_REG5 = 0x24;
uint8_t CTRL_REG6 = 0x25;
uint8_t OUT_X_L_Reg = 0x28;
uint8_t OUT_X_H_Reg = 0x29;
uint8_t OUT_Y_L_Reg = 0x2A;
uint8_t OUT_Y_H_Reg = 0x2B;
uint8_t OUT_Z_L_Reg = 0x2C;
uint8_t OUT_Z_H_Reg = 0x2D;

void WriteRegister(uint8_t reg, int val)
{
  Wire.beginTransmission(LIS3DH);      // sends device addr down SDA line of bus
  Wire.write(reg);  //chooses register address 
  Wire.write(val);  //sends value to chosen register address
  Wire.endTransmission(); 
}

uint8_t ReadRegister(uint8_t reg)
{
  Wire.beginTransmission(LIS3DH);
  Wire.write(reg);                //chooses register address          
  Wire.endTransmission(); 
  Wire.requestFrom(LIS3DH, 1);    //Request data written
  uint8_t read_reg = Wire.read(); // read byte requested
  return read_reg;
}

void CollectData()
{
   uint8_t OUT_X_L[1000];
   uint8_t OUT_X_H[1000];
   uint16_t OUT_X[1000];
   
   uint8_t OUT_Y_L[1000];
   uint8_t OUT_Y_H[1000];
   uint16_t OUT_Y[1000];
   
   uint8_t OUT_Z_L[1000];
   uint8_t OUT_Z_H[1000];
   uint16_t OUT_Z[1000];

 for(int i=0; i<1000; i++)
  {
    OUT_X_L[i]=ReadRegister(OUT_X_L_Reg);
    //Serial.println(OUT_Z_L[i]);
    OUT_X_H[i]=ReadRegister(OUT_X_H_Reg);
    //Serial.println(OUT_Z_H[i]);
    OUT_X[i]=(OUT_X_H[i]*256+OUT_X_L[i])/16;

    OUT_Y_L[i]=ReadRegister(OUT_Y_L_Reg);
    OUT_Y_H[i]=ReadRegister(OUT_Y_H_Reg);
    OUT_Y[i]=(OUT_Y_H[i]*256+OUT_Y_L[i])/16;
    
    OUT_Z_L[i]=ReadRegister(OUT_Z_L_Reg);
    OUT_Z_H[i]=ReadRegister(OUT_Z_H_Reg);
    OUT_Z[i]=(OUT_Z_H[i]*256+OUT_Z_L[i])/16;   
  }
  
  for(int j = 0; j<1000; j++)
  {
    //Serial.println(OUT_X[j]);
    //Serial.println(OUT_Y[j]);
    Serial.println(OUT_Z[j]);
  }

 }

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  WriteRegister(CTRL_REG1, 151);
  WriteRegister(CTRL_REG2, 0);
  WriteRegister(CTRL_REG3, 0);
  WriteRegister(CTRL_REG4, 9);
  WriteRegister(CTRL_REG5, 0);
  WriteRegister(CTRL_REG5, 0);
  //Serial.println(ReadRegister(CTRL_REG4));
}

void LIS3DH_read(uint16_t *x, uint16_t *y, uint16_t *z) {
  Wire.beginTransmission(LIS3DH);
  Wire.write(OUT_X_L_Reg | 0x80); // 0x80 for autoincrement
  Wire.endTransmission();

  Wire.requestFrom(LIS3DH, 6);
  *x = Wire.read();
  *x |= ((uint16_t)Wire.read()) << 8;
  *y = Wire.read();
  *y |= ((uint16_t)Wire.read()) << 8;
  *z = Wire.read();
  *z |= ((uint16_t)Wire.read()) << 8;
}

void loop() {
  uint16_t x, y, z;
  while(1) {
    LIS3DH_read(&x, &y, &z);
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.println();
    delay(1);
  }
  //CollectData();
}
