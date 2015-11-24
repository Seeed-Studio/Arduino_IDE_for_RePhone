
void setup() 
{
    delay(1000);
    Serial.begin(115200);
    Serial.print("uart test."); 
    delay(1000);
}

void loop() 
{ 
    unsigned int data;
    data = analogRead(A3); 
    Serial.print(data); 
    Serial.print("\r\n"); 
    delay(1000);
}
