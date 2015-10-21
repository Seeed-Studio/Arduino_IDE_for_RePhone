
#include <Wire.h>

#define    LED_B    2
#define    LED_G    4
#define    LED_R    3

#define    LED_ON     0
#define    LED_OFF    1

unsigned char slaveScan[3] = {0,0,0};
unsigned char slaveData[5][8] = 
{
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};

void setup() 
{
    Serial1.begin(115200);
    Serial1.print("Boot test.\r\n");
    
    pinMode(LED_B,OUTPUT);
    pinMode(LED_G,OUTPUT);
    pinMode(LED_R,OUTPUT);
    digitalWrite(LED_B,LED_OFF);
    digitalWrite(LED_G,LED_OFF);
    digitalWrite(LED_R,LED_OFF);
    
    Wire.begin();
    
    slaveDataClear();
}

void loop() 
{
        slave_scan_get();
        slave_data_get();
        slave_check();
        slaveDataClear();
        delay(500);
}

void slave_scan_get()
{
    unsigned char i = 0;
    Wire.beginTransmission(3);
    Wire.write(0x88);
    Wire.endTransmission();
    Wire.requestFrom(3, 3);
    while(Wire.available())
    {
        slaveScan[i++] = Wire.read();
    }
}

void slave_data_get()
{
    for(unsigned char i = 0;i<5;i++)
    {
        unsigned char j = 0;
        Wire.beginTransmission(3);
        Wire.write(0x80);
        Wire.write(i | 0x40);
        Wire.endTransmission();
        Wire.requestFrom(3, 8);
        while(Wire.available())
        {
            slaveData[i][j++] = Wire.read();
        }
    }
}

void slave_check()
{    
    unsigned char i;
    unsigned char j;
    
    Serial1.print("Slave scan data is:\r\n");
    for(i=0;i<3;i++)
    {
        Serial1.print("0x");
        Serial1.print(slaveScan[i],HEX);
        Serial1.print(" ");
    }
    Serial1.print("\r\n");
    
    Serial1.print("Slave sensor data is:\r\n");
    for(i=0;i<5;i++)
    {
        for(j=0;j<8;j++)
        {
            Serial1.print("0x");
            Serial1.print(slaveData[i][j],HEX);
            Serial1.print(" ");
            if(j == 0)
            {
                switch(i)
                {
                    case 0:
                    case 1:
                    case 2:
                    if(slaveData[i][j] == 0)digitalWrite(LED_R,LED_ON);
                    else                    digitalWrite(LED_R,LED_OFF);
                    break;
                    
                    case 3:
                    if(slaveData[i][j] == 1)digitalWrite(LED_G,LED_ON);
                    else                    digitalWrite(LED_G,LED_OFF);
                    break;
                    
                    case 4:
                    if(slaveData[i][j] == 2)digitalWrite(LED_B,LED_ON);
                    else                    digitalWrite(LED_B,LED_OFF);
                    break;
                    
                    default:
                    break;
                }
            }
        }
        Serial1.print("\r\n");
    }
    Serial1.print("\r\n");
}

void slaveDataClear()
{
    unsigned char i,j;
    for(i=0;i<3;i++)
    {
        slaveScan[i] = 0xff;
    }
    for(i=0;i<5;i++)
    {
        for(j=0;j<8;j++)
        {
            slaveData[i][j] = 0xff;
        }
    }
}
