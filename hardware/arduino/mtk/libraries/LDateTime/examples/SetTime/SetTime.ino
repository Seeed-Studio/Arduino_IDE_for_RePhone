// set time
#include <LDateTime.h>

datetimeInfo t;

// set time to 17:06:37 Oct29, 2015
void time_init()
{
    t.year  = 2015;
    t.mon   = 10;
    t.day   = 29;
    t.hour  = 17;
    t.min   = 6;
    t.sec   = 37;
}


void setup()
{
    Serial.begin(115200);
    
    time_init();
    LDateTime.setTime(&t);
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