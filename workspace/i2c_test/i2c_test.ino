
#include <Wire.h>

void setup()
{
    //Hardware Serial Initial
    Serial1.begin(115200);
    Serial1.print("I2C Master.\r\n");
    Serial.begin(115200);
    Serial.print("I2C Master.\r\n");
    //I2C Initial
    Wire.begin();
    
    //pinMode(8,OUTPUT);
}
unsigned char data = 0;

void loop()
{   
    
    Wire.beginTransmission(3);
    Wire.write(0x88);
    Wire.endTransmission();
    Wire.requestFrom(3, 3);
    Serial1.print("\r\n");
    Serial1.print("Scan flag: ");
    while(Wire.available())
    {
        Serial1.print("0x");
        Serial1.print(Wire.read(),HEX);
        Serial1.print(" ");
    }
    Serial1.print("\r\n");
    
    /*
    for(unsigned char i = 0;i<5;i++)
    {
        Wire.beginTransmission(3);
        Wire.write(0x80);
        Wire.write(i | 0x40);
        Wire.endTransmission();
        Wire.requestFrom(3, 8);
        Serial.print("\r\n");
        Serial.print("Read  ");
        while(Wire.available())
        {
            Serial.print("0x");
            Serial.print(Wire.read(),HEX);
            Serial.print(" ");
        }
        Serial1.print("\r\n");
    }
    */
    //digitalWrite(8,data%2);
    //data ++;
    delay(1000);
}
