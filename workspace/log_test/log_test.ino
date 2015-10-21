
#include <LPrintlog.h>

void setup() 
{
    Serial1.begin(115200);
    Serial1.print("\r\n");
    
}

void loop() 
{
    LPrintlog.LPrintLogInfo("ABCD");
    LPrintlog.LPrintLogDebug("ABCD");
    Serial1.print("ABCD\r\n");
    delay(1000);
}
