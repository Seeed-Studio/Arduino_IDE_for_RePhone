/*
  RePhone audio test Demo
  First you need to put a mp3 file to storage
  Then open the Serial monitor, input number to change the status
  1 - Play
  2 - Setvolume
  3 - Pause
  4 - Resume
  5 - Stop
*/
#include <LAudio.h>

// add your music file name here
#define    FILE_NAME    "music.mp3"

#define    LED_B        2
#define    LED_G        4
#define    LED_R        3
#define    LED_ON       0
#define    LED_OFF      1

#define    PLAY         1
#define    SETVOLUME    2
#define    PAUSE        3
#define    RESUME       4
#define    STOP         5

unsigned char Status_Value = STOP;

int volume = 6;

void changeVolume()
{
    volume++;
    volume = volume>6 ? 1 : volume;
}

void setup()
{
    LAudio.begin();
    Serial.begin(115200);
    Serial.println("Play      - 1");
    Serial.println("Setvolume - 2");
    Serial.println("Pause     - 3");
    Serial.println("Resume    - 4");
    Serial.println("Stop      - 5");
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
        Serial.print("LAudio status is ");
        Serial.println(status);
    }

    if(status == AudioEndOfFile)
    {
        Status_Value = PLAY;
        Change_Status(Status_Value);
    }
}

void Change_Status(unsigned char status)
{
    switch(status)
    {
        case 1:
        LAudio.playFile( storageFlash,(char*)"music.mp3");
        LAudio.setVolume(volume);
        Serial.println("playOne");
        break;

        case 2:
        LAudio.setVolume(volume);
        changeVolume();
        Serial.print("set volume to ");
        Serial.println(volume);
        break;

        case 3:
        LAudio.pause();
        Serial.println("pause");
        break;

        case 4:
        LAudio.resume();
        Serial.println("resume");
        break;

        case 5:
        LAudio.stop();
        Serial.println("stop");
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
    while(Serial.available() > 0)
    {
        unsigned char inChar = Serial.read();
        inString += (char)inChar;
        dataTemp1[bitCount] = inChar - '0';
        bitCount += 1;
        delay(10);
    }
    if(inString != "")
    {
        if(bitCount > 4)
        {
            Serial.println("Key input error.");
        }
        else
        {
            for(char i=0;i<bitCount;i++)
            {
                unsigned int dataTemp2 = 1;
                for(char j=0;j<(bitCount-i-1);j++)dataTemp2 *= 10;
                keyValue += (dataTemp1[i] * dataTemp2);
            }
            Serial.print("Key value is: ");
            Serial.println(keyValue);
        }
    }
    return keyValue;
}
