
#include <LLedMatrix.h>

void setup() 
{
    Serial.begin(115200);
    Serial.print("Led Matrix test.\r\n");
    LedMatrix.check_on_line();
}

void loop() 
{
    LedMatrix.disp_string("ABCD",4,200);
    delay(4500);
    LedMatrix.disp_char(' ',500);
    delay(1000);
    LedMatrix.disp_char('W',500);
    delay(1000);
    LedMatrix.disp_char('a',500);
    delay(1000);
    LedMatrix.disp_char('y',500);
    delay(1000);
    LedMatrix.disp_char('e',500);
    delay(1000);
    LedMatrix.disp_char('n',500);
    delay(1000);

    LedMatrix.disp_pic(0,500);
    delay(1500);
    LedMatrix.disp_pic(1,500);
    delay(1500);
    LedMatrix.disp_pic(2,500);
    delay(1500);
    LedMatrix.disp_pic(3,500);
    delay(1500);
}
