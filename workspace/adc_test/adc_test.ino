
void setup() 
{
    delay(1000);
    Serial1.begin(115200);
    Serial1.print("uart test."); 
    //analogWrite(0,512);
    analogWrite(5,256);
    delay(1000);
}

void loop() 
{ 
    unsigned int data;
    data = analogRead(A3); 
    Serial1.print(data); 
    Serial1.print("\r\n"); 
    delay(1000);
}
