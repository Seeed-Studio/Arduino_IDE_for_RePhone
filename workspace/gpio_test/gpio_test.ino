
void setup() 
{
    //Serial1.begin(115200);
    //Serial1.println("uart test."); 
    
    //pinMode(0,OUTPUT);
    pinMode(1,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);    
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    //pinMode(10,OUTPUT);
    //pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
    pinMode(15,OUTPUT);
    
    //pinMode(A0,OUTPUT);
    //pinMode(A1,OUTPUT);
    pinMode(A2,OUTPUT);
    pinMode(A3,OUTPUT);
    pinMode(E4,OUTPUT);
    
    //LTask.remoteCall(gpio_init,NULL);
    //pinMode(1,INPUT);
    //pinMode(9,OUTPUT);
    delay(1000);
}

void loop() 
{  
    //digitalWrite(0,LOW);
    digitalWrite(1,LOW);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    //digitalWrite(10,LOW);
    //digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    digitalWrite(14,LOW);
    digitalWrite(15,LOW);
    //digitalWrite(A0,LOW);
    //digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    digitalWrite(A3,LOW);
    digitalWrite(E4,LOW);
    //LTask.remoteCall(gpio_set,NULL);
    delay(1000);

    //digitalWrite(0,HIGH);
    digitalWrite(1,HIGH);
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    //digitalWrite(10,HIGH);
    //digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,HIGH);
    digitalWrite(14,HIGH);
    digitalWrite(15,HIGH);
    //digitalWrite(A0,HIGH);
    //digitalWrite(A1,HIGH);
    digitalWrite(A2,HIGH);
    digitalWrite(A3,HIGH);
    digitalWrite(E4,HIGH);
    //LTask.remoteCall(gpio_clr,NULL);
    delay(1000);
}
/*
unsigned char data;
data  = digitalRead(1);
if(data)
{
    //digitalWrite(9,HIGH);
    Serial1.println("Pin is High."); 
}
else 
{
    //digitalWrite(9,LOW);
    Serial1.println("Pin is Low."); 
}
delay(200);
*/
