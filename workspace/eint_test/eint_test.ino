
unsigned char flag = 0;
unsigned char flagLast = 0;

void setup() 
{
    Serial.begin(115200);
    Serial.print("ENIT test.\r\n");
    attachInterrupt(E1,interruptServer,FALLING);
}

void loop() 
{
    if(flagLast != flag)
    {
        flagLast = flag;
        Serial.print("There is a interrupt coming.\r\n");
    }
    delay(100);
}

void interruptServer()
{
    flag = !flag;
}
