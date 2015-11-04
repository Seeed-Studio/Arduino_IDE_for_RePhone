/*
  Battery Test
  Open Serial monitor to get the charging status.
*/

#include <LBattery.h>

void setup() 
{
    Serial.begin(115200);
    Serial.print("Battery test.\r\n");
}

void loop() 
{
    int batteryLlevel;
    
    batteryLlevel = LBattery.level();
    Serial.print("Battery level is ");
    Serial.println(batteryLlevel);

    if(LBattery.isCharging())Serial.print("Battery in charging state.\r\n");
    else Serial.print("Battery not in charging state.\r\n");
    
    delay(1000);
}
