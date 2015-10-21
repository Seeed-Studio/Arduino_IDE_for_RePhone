
#include <LDisplay.h>
#include <LSensorHub.h>

void setup()
{
    Serial1.begin(115200);
    Serial1.print("Sensor Hub test.\r\n");
    Lcd.init();
    Lcd.font_init();
    Lcd.back_light_level(50);
    Lcd.screen_set(0xffff00);
    Lcd.draw_font(0, 0, "Sensor Hub test", 0xffff00, 0);
    if(LSensorHub.check_on_line() == false)
    {
        Lcd.draw_font(0, 20, "Sensor Hub off-line", 0xffff00, 0);
        while(1);
    }
}

void loop()
{
    long data1 = 0;
    long data2 = 0;
    long data3 = 0;
    unsigned long data4 = 0;
    long data5 = 0;
    
    LSensorHub.GetAccData(&data1, &data2, &data3);
    LSensorHub.GetLighData(&data4);
    LSensorHub.GetTempData(&data5);
    
    Lcd.draw_font(0, 20, "Acc X:        ", 0xffff00, 0);
    if(data1 > 0)
    {
        Lcd.draw_font(9*9, 20, "+", 0xffff00, 0);
	Lcd.draw_number(9*10, 20, data1, 0xffff00, 0);
    }
    else
    {
        data1 ^= 0xffffffff;
        data1 += 1;
        Lcd.draw_font(9*9, 20, "-", 0xffff00, 0);
	Lcd.draw_number(9*10, 20, data1, 0xffff00, 0);
    }
    Lcd.draw_font(9*16, 20, "mg", 0xffff00, 0);
    
    Lcd.draw_font(0, 40, "Acc Y:        ", 0xffff00, 0);
    if(data2 > 0)
    {
        Lcd.draw_font(9*9, 40, "+", 0xffff00, 0);
	Lcd.draw_number(9*10, 40, data2, 0xffff00, 0);
    }
    else
    {
        data2 ^= 0xffffffff;
        data2 += 1;
        Lcd.draw_font(9*9, 40, "-", 0xffff00, 0);
	Lcd.draw_number(9*10, 40, data2, 0xffff00, 0);
    }
    Lcd.draw_font(9*16, 40, "mg", 0xffff00, 0);
    
    Lcd.draw_font(0, 60, "Acc Z:        ", 0xffff00, 0);
    if(data3 > 0)
    {
        Lcd.draw_font(9*9, 60, "+", 0xffff00, 0);
	Lcd.draw_number(9*10, 60, data3, 0xffff00, 0);
    }
    else
    {
        data3 ^= 0xffffffff;
        data3 += 1;
        Lcd.draw_font(9*9, 60, "-", 0xffff00, 0);
	Lcd.draw_number(9*10, 60, data3, 0xffff00, 0);
    }
    Lcd.draw_font(9*16, 60, "mg", 0xffff00, 0);
    
    Lcd.draw_font(0, 80, "Light:      ", 0xffff00, 0);
    Lcd.draw_number(9*10, 80, data4, 0xffff00, 0);
    Lcd.draw_font(9*16, 80, "Lux", 0xffff00, 0);
    
    Lcd.draw_font(0, 100, "Temp:     ", 0xffff00, 0);
    Lcd.draw_number(9*10, 100, data5, 0xffff00, 0);
    Lcd.draw_font(9*16, 100, "'C", 0xffff00, 0);
    delay(100);
}
