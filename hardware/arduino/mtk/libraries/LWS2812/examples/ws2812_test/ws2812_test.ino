
#include <LWs2812.h>

void setup() 
{
    Serial1.begin(115200);
    Serial1.print("Ws2812 test.\r\n");
    LWs2812.check_on_line();
}

void loop()
{
    LWs2812.monochrome(5, 0x00ff0000, 2000);
    delay(2500);
    LWs2812.marquee(5, 0x00ffff00, 5000);
    delay(5500);
    LWs2812.rainbow(5, 5000);
    delay(5500);
}
