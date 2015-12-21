
#define GPIO_50  15
#define GPIO_49  14
#define GPIO_48  13
#define GPIO_47  12
#define GPIO_46  E4
#define GPIO_44  7
#define GPIO_43  6
#define GPIO_29  3
#define GPIO_28  4
#define GPIO_27  2
#define GPIO_19  5
#define GPIO_11  8
#define GPIO_10  9
#define GPIO_03  1
#define GPIO_02  A3
#define GPIO_01  A2


void setup() 
{
    pinMode(GPIO_50, OUTPUT);
    pinMode(GPIO_49, OUTPUT);
    pinMode(GPIO_48, OUTPUT);
    pinMode(GPIO_47, OUTPUT);
    pinMode(GPIO_46, OUTPUT);
    pinMode(GPIO_44, OUTPUT);
    pinMode(GPIO_43, OUTPUT);
    pinMode(GPIO_29, OUTPUT);
    pinMode(GPIO_28, OUTPUT);
    pinMode(GPIO_27, OUTPUT);
    pinMode(GPIO_19, OUTPUT);
    pinMode(GPIO_11, OUTPUT);
    pinMode(GPIO_10, OUTPUT);
    pinMode(GPIO_03, OUTPUT);
    pinMode(GPIO_02, OUTPUT);
    pinMode(GPIO_01, OUTPUT);
}

void loop() 
{  
    digitalWrite(GPIO_50, HIGH);
    digitalWrite(GPIO_49, HIGH);
    digitalWrite(GPIO_48, HIGH);
    digitalWrite(GPIO_47, HIGH);
    digitalWrite(GPIO_46, HIGH);
    digitalWrite(GPIO_44, HIGH);
    digitalWrite(GPIO_43, HIGH);
    digitalWrite(GPIO_29, HIGH);
    digitalWrite(GPIO_28, HIGH);
    digitalWrite(GPIO_27, HIGH);
    digitalWrite(GPIO_19, HIGH);
    digitalWrite(GPIO_11, HIGH);
    digitalWrite(GPIO_10, HIGH);
    digitalWrite(GPIO_03, HIGH);
    digitalWrite(GPIO_02, HIGH);
    digitalWrite(GPIO_01, HIGH);
    delay(1000);
    
    digitalWrite(GPIO_50, LOW);
    digitalWrite(GPIO_49, LOW);
    digitalWrite(GPIO_48, LOW);
    digitalWrite(GPIO_47, LOW);
    digitalWrite(GPIO_46, LOW);
    digitalWrite(GPIO_44, LOW);
    digitalWrite(GPIO_43, LOW);
    digitalWrite(GPIO_29, LOW);
    digitalWrite(GPIO_28, LOW);
    digitalWrite(GPIO_27, LOW);
    digitalWrite(GPIO_19, LOW);
    digitalWrite(GPIO_11, LOW);
    digitalWrite(GPIO_10, LOW);
    digitalWrite(GPIO_03, LOW);
    digitalWrite(GPIO_02, LOW);
    digitalWrite(GPIO_01, LOW);
    delay(1000);
}

