#include <LCheckSIM.h>

char buff[256];

void setup() 
{
  // put your setup code here, to run once:
   Serial.begin(115200);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  sprintf(buff,"is check = %d",LCheckSIM.isCheck() );
  Serial.println(buff);
  delay(1000); 
}
