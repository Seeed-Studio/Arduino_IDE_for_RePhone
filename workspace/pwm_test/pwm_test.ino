

void setup()
{
    Serial.begin(115200);
    Serial.println("pwm test.\r\n");   
      
    analogWrite(0, 512);
    analogWrite(1, 256);
    
    //analogWriteAdvance(0, 0, 0, 1022, 512);
    //analogWriteAdvance(1, 0, 0, 1022, 256);
}

void loop()
{
    Serial.println("time loop.\r\n"); 
    delay(1000);
}
