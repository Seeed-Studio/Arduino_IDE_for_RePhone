
#define PIN_INT1  E2
#define PIN_INT2  E1
#define PIN_SCL   6
#define PIN_SDA   7

void setup()
{
    pinMode(PIN_INT1, OUTPUT);
    pinMode(PIN_INT2, OUTPUT);
    pinMode(PIN_SCL, OUTPUT);
    pinMode(PIN_SDA, OUTPUT);
}

void loop()
{
    digitalWrite(PIN_INT1, HIGH);
    digitalWrite(PIN_INT2, LOW);
    digitalWrite(PIN_SCL, HIGH);
    digitalWrite(PIN_SDA, LOW);
    delay(1000);
    digitalWrite(PIN_INT1, LOW);
    digitalWrite(PIN_INT2, HIGH);
    digitalWrite(PIN_SCL, LOW);
    digitalWrite(PIN_SDA, HIGH);
    delay(1000);
}
