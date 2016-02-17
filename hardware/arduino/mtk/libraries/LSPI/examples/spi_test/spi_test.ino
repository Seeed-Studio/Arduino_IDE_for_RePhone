#include <LSPI.h>


void setup() 
{
    Serial.begin(115200);
    LSPI.begin();
}

void loop() 
{
    unsigned char data;
    data = LSPI.transfer(0x55);
    Serial.println(data);
    delay(1000); 
}
