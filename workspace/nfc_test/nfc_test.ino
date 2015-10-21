
#include <LNFC.h>
#include <LDisplay.h>
#include <stdio.h>


unsigned char number = 0;

void setup()
{
    Serial1.begin(9600);
    Serial1.print("NFC test.\r\n");
    Lcd.init();
    Lcd.font_init();
    Lcd.back_light_level(50);
    Lcd.screen_set(0xffffff);
}

unsigned char data = 0;
void loop()
{  
    unsigned char *str = 0;
    char buffer[50] = {0,};
    
    if(LNFC.check_online())
    {
        LNFC.adapter_init();
        delay(50);
        str = LNFC.adapter_get_uid();
        //sprintf(buffer, "NFC uid is 0x%x 0x%x 0x%x 0x%x\r\n", str[2],str[3],str[4],str[5]);
        //Lcd.draw_font(0, 0, buffer, 0xffffff, 0);
        //Serial1.print(buffer);
        Lcd.draw_font(0, 0, "                         ", 0xffffff, 0);
        Lcd.draw_number(0, 0, str[2], 0xffffff, 0);
        Lcd.draw_number(50, 0, str[3], 0xffffff, 0);
        Lcd.draw_number(100, 0, str[4], 0xffffff, 0);
        Lcd.draw_number(150, 0, str[5], 0xffffff, 0);
    }
    
    Lcd.draw_number(0, 20, data++, 0xffffff, 0);
    delay(1000);
}

