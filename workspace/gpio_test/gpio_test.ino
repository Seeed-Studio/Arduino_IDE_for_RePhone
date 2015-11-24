
#define    LED_B    GPIO12
#define    LED_G    GPIO15
#define    LED_R    GPIO17

#define    LED_ON     0
#define    LED_OFF    1

void setup() 
{
    pinMode(LED_B,OUTPUT);
    pinMode(LED_G,OUTPUT);
    pinMode(LED_R,OUTPUT);
    digitalWrite(LED_B,LED_OFF);
    digitalWrite(LED_G,LED_OFF);
    digitalWrite(LED_R,LED_OFF);
}

void loop() 
{
    digitalWrite(LED_B,LED_OFF);
    digitalWrite(LED_G,LED_OFF);
    digitalWrite(LED_R,LED_OFF);
    delay(1000);
    digitalWrite(LED_B,LED_ON);
    digitalWrite(LED_G,LED_ON);
    digitalWrite(LED_R,LED_ON);
    delay(1000);
}

