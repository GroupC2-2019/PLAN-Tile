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
   uint8_t OUT_X_L[10];
   uint8_t OUT_X_H[10];
   uint8_t OUT_X[10];
   
   uint8_t OUT_Y_L[10];
   uint8_t OUT_Y_H[10];
   uint8_t OUT_Y[10];
   
   uint8_t OUT_Z_L[10];
   uint8_t OUT_Z_H[10];
   uint8_t OUT_Z[10];

  uint8_t test_L=ReadRegister(OUT_Z_L_Reg);
  uint8_t test_H=ReadRegister(OUT_Z_H_Reg);
  uint8_t test=(test_H*256+test_L)/16;
 /* for(int i=0; i<100; i++)
  {
    OUT_Z_L[i]=ReadRegister(OUT_Z_L_Reg);
    OUT_Z_H[i]=ReadRegister(OUT_Z_H_Reg);
  }
  for(int j = 0; j<100; j++)
  {
    OUT_Z[j]=(OUT_Z_H[j]*256+OUT_Z_L[j])/16;
    Serial.println(OUT_Z[100]);
  }*/
  
  //Serial.println(test_L);
  //Serial.println(test_H);  
  //Serial.println(test);
  //delay(1000);
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

void loop() {
  CollectData();
  //Serial.println(ReadRegister(OUT_Z_L_Reg));  

}
