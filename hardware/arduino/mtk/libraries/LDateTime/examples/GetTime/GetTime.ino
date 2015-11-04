// get time and print to Serial monitor
#include <LDateTime.h>

datetimeInfo t;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    // display time;
    LDateTime.getTime(&t);
    
    char str[100];
    sprintf(str, "%d:%d:%d, %d-%d-%d", t.hour, t.min, t.sec, t.mon, t.day, t.year);
    Serial.println(str);
    delay(1000);  
}