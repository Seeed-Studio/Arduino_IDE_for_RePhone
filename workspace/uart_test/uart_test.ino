
void setup() 
{
    Serial1.begin(115200);
    Serial.begin(115200);
    Serial1.print("uart test."); 
    Serial.print("uart test.");
}
unsigned char data = 0;
void loop() 
{
     Serial1.print("New data is ");
     Serial1.println(data++);
     Serial.println(data++);
     delay(1000);
}
