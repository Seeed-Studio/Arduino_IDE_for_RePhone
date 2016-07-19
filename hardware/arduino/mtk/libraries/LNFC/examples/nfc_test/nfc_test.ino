
#include <LNFC.h>
#include <stdio.h>


void setup()
{
    Serial.begin(115200);
    Serial.print("NFC test.\r\n");
    
    while(1)
    {
        if(LNFC.check_on_line())
        {
            Serial.println("On-line!");
            break;
        }
        else Serial.println("Off-line!");
        delay(1000);
    }
    
    LNFC.adapter_init();
    delay(1000);
}
    
void loop()
{  
    unsigned char *str = 0;
    char buffer[50] = {0,};
    
    str = LNFC.adapter_get_uid();
    sprintf(buffer, "NFC uid is 0x%x 0x%x 0x%x 0x%x\r\n", str[2],str[3],str[4],str[5]);
    Serial.print(buffer);
    
    delay(1000);
}

