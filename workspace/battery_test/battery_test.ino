
#include <LBattery.h>
//#include <LPrintlog.h>

void setup() 
{
    Serial1.begin(115200);
    Serial1.print("Battery test.\r\n");
}

void loop() 
{
    int batteryLlevel;
    
    batteryLlevel = LBattery.level();
    Serial1.print("Battery level is ");
    Serial1.println(batteryLlevel);
    //LPrintlog.LPrintLogDebug("Battery level is ");
    //LPrintlog.LPrintLogDebug(&batteryLlevel);
    
    if(LBattery.isCharging())Serial1.print("Battery in charging state.\r\n");
    else Serial1.print("Battery not in charging state.\r\n");
    
    delay(1000);

}
