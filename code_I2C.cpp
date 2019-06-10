#include <Wire.h>
void setup() 
{
  Serial.begin(9600);                            
  Wire.begin();                                  
  Wire.beginTransmission(0x44);                  
  Wire.write(0x01);                             
  Wire.write(0xCE);
  Wire.write(0x10);                              
  Wire.endTransmission();
}
void loop() 
{
  Wire.beginTransmission(0x44);
  Wire.write(0x00);                              
  Wire.endTransmission();
  delay(200);
  
  Wire.requestFrom(0x44, 2);                     
  uint16_t bitLux;
  uint8_t  buff[2];
  while (Wire.available()) 
  { 
    Wire.readBytes(buff, 2);
    bitLux = (buff[0] << 8) | buff[1];
    float decLux = converter(bitLux);   
    Serial.println(decLux);           
    if (decLux<=40.0)
    {
      digitalWrite(13, HIGH);             
    }
    else
    {
      digitalWrite(13, LOW);
    }
  }
  delay(1000);
}
float converter(uint16_t twobytes)
{
  uint16_t expo, mant;
  mant = twobytes & 0x0FFF;                 
  expo = (twobytes & 0xF000) >> 12;          
  return mant * (0.01 * pow(2, expo)); 
}