#include <LAudio.h>

#define    LED_B    2
#define    LED_G    4
#define    LED_R    3
#define    LED_ON     0
#define    LED_OFF    1

#define    PLAY         1
#define    SETVOLUME    2
#define    PAUSE        3
#define    RESUME       4
#define    STOP         5

unsigned char Status_Value = STOP;


void setup()
{
  LAudio.begin();
  Serial1.begin(115200);
  Serial1.println("Play      - 1");
  Serial1.println("Setvolume - 2");
  Serial1.println("Pause     - 3");
  Serial1.println("Resume    - 4");
  Serial1.println("Stop      - 5");
  pinMode(LED_B,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_R,OUTPUT);
  digitalWrite(LED_B,LED_OFF);
  digitalWrite(LED_G,LED_OFF);
  digitalWrite(LED_R,LED_OFF);
  Change_Status(PLAY);
}

char StatusFlag = 0;

void loop()
{
   unsigned char KEY_NUM;
   AudioStatus status;
   
   KEY_NUM = task_uart_key();
   
   if(KEY_NUM > 0)
   { 
       Change_Status(KEY_NUM);
       KEY_NUM = 0;
   }
   
   status = LAudio.getStatus(); 
   if(StatusFlag != status)
   {
       StatusFlag = status;
       Serial1.print("LAudio status is ");
       Serial1.println(status);
   }
   
   if(status == AudioEndOfFile)
   {
     Status_Value = PLAY;
     Change_Status(Status_Value);
   }
   digitalWrite(LED_B,LED_OFF);
   delay(1000);
   digitalWrite(LED_B,LED_ON);
   delay(1000);
}

void Change_Status(unsigned char status)
{
  switch(status)
  {
    case 1:
    LAudio.playFile( storageFlash,(char*)"R2D2.mp3");
    LAudio.setVolume(6);
    Serial1.println("playOne");
    break;
    
    case 2:
    LAudio.setVolume(6);
    Serial1.println("setVolume");
    break;
    
    case 3:
    LAudio.pause();
    Serial1.println("pause");
    break;
    
    case 4:
    LAudio.resume();
    Serial1.println("resume");
    break;
    
    case 5:
    LAudio.stop();
    Serial1.println("stop");
    break;
    
    default:
    break;
  }
}

unsigned int task_uart_key()
{
    String inString = "";
    unsigned int keyValue = 0;
    unsigned char bitCount = 0; 
    unsigned char dataTemp1[10] = {0};
    while(Serial1.available() > 0)
    {
            unsigned char inChar = Serial1.read();
            inString += (char)inChar;
            dataTemp1[bitCount] = inChar - '0';
            bitCount += 1;
            delay(10);
    }
    if(inString != "")
    {
            if(bitCount > 4)
            {
                Serial1.println("Key input error.");
            }
            else
            {
                    for(char i=0;i<bitCount;i++)
                    {
                            unsigned int dataTemp2 = 1;
                            for(char j=0;j<(bitCount-i-1);j++)dataTemp2 *= 10;
                            keyValue += (dataTemp1[i] * dataTemp2);
                    }   
                    Serial1.print("Key value is: ");
                    Serial1.println(keyValue); 
            }
    }
    return keyValue;   
}
