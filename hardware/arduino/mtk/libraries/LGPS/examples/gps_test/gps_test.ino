#include <LGPS.h>
#include <stdio.h>

void setup()
{
    Serial.begin(115200);
    Serial.print("GPS test.\r\n");
}

void loop()
{
    unsigned char *utc_date_time = 0;
    char buffer[50] = {0,};
    
    if(LGPS.check_online())
    {
        utc_date_time = LGPS.get_utc_date_time();
        sprintf(buffer, "GPS UTC:%d-%d-%d  %d:%d:%d\r\n", utc_date_time[0], utc_date_time[1], utc_date_time[2], utc_date_time[3], utc_date_time[4],utc_date_time[5]);
        Serial.print(buffer);
        
        sprintf(buffer, "GPS status is %c\r\n", LGPS.get_status());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS latitude is %c:%f\r\n", LGPS.get_ns(), LGPS.get_latitude());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS longitude is %c:%f\r\n", LGPS.get_ew(), LGPS.get_longitude());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS speed is %f\r\n", LGPS.get_speed());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS course is %f\r\n", LGPS.get_course());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS position fix is %c\r\n", LGPS.get_position_fix());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS sate used is %d\r\n", LGPS.get_sate_used());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS altitude is %f\r\n", LGPS.get_altitude());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS mode is %c\r\n", LGPS.get_mode());
        Serial.print(buffer);
        
        sprintf(buffer, "GPS mode2 is %c\r\n", LGPS.get_mode2());
        Serial.print(buffer);
    }    
    delay(1000);
}
