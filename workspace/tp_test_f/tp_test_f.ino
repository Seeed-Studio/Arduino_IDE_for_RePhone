
#include <LFTouch.h>
#include <LDisplay.h>

unsigned char eintFlag = 0;
void setup()
{
    //Serial1.begin(115200);
    //Serial1.print("Touch test.\r\n");
    attachInterrupt(E3,interruptServer,FALLING);
    Tp.Init();
    Lcd.Init();
    Lcd.FontInit();
    Lcd.BackLightLevel(50);
    Lcd.ScreenSet(0xffff00);
    Lcd.daw_font(0, 0, "Touch test", 0xffff00, 0);
}
void loop()
{
    if(eintFlag)
    {
        eintFlag = 0;
        unsigned char x = 0;
        unsigned char y = 0;
        Tp.Get_xy(&x,&y);
        Lcd.daw_font(0, 20, "X is   ", 0xffff00, 0);
        Lcd.daw_font(110, 20, "Y is   ", 0xffff00, 0);
        Lcd.daw_number(40, 20, x, 0xffff00, 0);
        Lcd.daw_number(150, 20, y, 0xffff00, 0);
    }
    delay(200);
}
void interruptServer()
{
    eintFlag = 1;
}
