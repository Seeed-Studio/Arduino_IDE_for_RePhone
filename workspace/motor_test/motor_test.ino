
#include <LMotor.h>

void setup()
{
    Serial1.begin(115200);
    Serial1.print("Motor test.\r\n");
    LMotor.check_on_line();
}

void loop()
{
    LMotor.set_mode(MOTOR_MODE_SHORT);
    delay(1000);
    LMotor.set_mode(MOTOR_MODE_LONG);
    delay(3000);
    LMotor.set_mode(MOTOR_MODE_INTERVAL);
    delay(4000);
}
