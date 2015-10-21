
#include <LGTouch.h>
#include <LDisplay.h>


unsigned char eintFlag = 0;
char EVENT = 0;
int X = 0;
int Y = 0;
        
void setup()
{
    //Serial1.begin(115200);
    //Serial1.print("Touch test.\r\n");
    Tp.Init();
    //Tp.Event_handle(touch_event_handle);
    Lcd.init();
    Lcd.font_init();
    Lcd.back_light_level(50);
    Lcd.screen_set(0xffff00);
    Lcd.draw_font(0, 0, "Touch test", 0xffff00, 0);
}
void loop()
{
    /*
    if(eintFlag)
    {
        eintFlag = 0;
        Lcd.daw_font(0, 20, "event is  ", 0xffff00, 0);
        Lcd.daw_number(80, 20, EVENT, 0xffff00, 0);
        Lcd.daw_font(0, 40, "x is    ", 0xffff00, 0);
        Lcd.daw_number(40, 40, X, 0xffff00, 0);
        Lcd.daw_font(0, 60, "y is   ", 0xffff00, 0);
        Lcd.daw_number(40, 60, Y, 0xffff00, 0);
    }
    */
    if(Tp.Event_available())
    {
        Tp.Get_event_xy(&EVENT, &X, &Y);
        Lcd.draw_font(0, 20, "event is  ", 0xffff00, 0);
        Lcd.draw_number(80, 20, EVENT, 0xffff00, 0);
        Lcd.draw_font(0, 40, "x is    ", 0xffff00, 0);
        Lcd.draw_number(40, 40, X, 0xffff00, 0);
        Lcd.draw_font(0, 60, "y is   ", 0xffff00, 0);
        Lcd.draw_number(40, 60, Y, 0xffff00, 0);
    }
    delay(50);
}
/*
void touch_event_handle(char event, int x, int y)
{
    EVENT = event;
    X = x;
    Y = y;
    eintFlag = 1;
}
*/

