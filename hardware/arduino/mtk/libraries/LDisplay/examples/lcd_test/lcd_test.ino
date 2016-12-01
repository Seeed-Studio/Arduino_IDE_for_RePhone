// LCD display test

#include <LDisplay.h>

unsigned long sysData = 0;

void setup()
{
    Serial.begin(115200);
    Serial.print("LCD display test.\r\n");
    Lcd.init();
    Lcd.font_init();
    Lcd.back_light_level(50);
    
    Lcd.screen_set(0xffff00);
    Lcd.draw_font(0, 0, "Xadow Phone Test.", 0xff00ff, 0, 20);
    Lcd.draw_updata();
    
    for(unsigned char j=0;j<20;j++)
    for(unsigned char i=0;i<240;i++)
    Lcd.draw_point(i,j+ 40,0xff0000);
    Lcd.draw_updata();
    
    Lcd.draw_line(0,200,239,200,0x00ff00);
    Lcd.draw_line(200,0,200,239,0x00ff00);
    Lcd.draw_fill_rectangle(100,100,130,130,0x0000f0);
    Lcd.draw_fill_rectangle(120,120,160,160,0x0000f0);
    Lcd.draw_updata();
}

void loop()
{
    sysData++;
    if(sysData >= 100)sysData = 0;
    Lcd.draw_fill_rectangle(0,80,80,160,0xffff00);
    Lcd.draw_number(0, 80, sysData, 0xffff00, 0, 64);
    Lcd.draw_font(70, 80, "*", 0xffff00, 0xff0000, 32);
    Lcd.draw_updata();
    delay(1000);
}

