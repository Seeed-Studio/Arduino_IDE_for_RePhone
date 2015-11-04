
#include <LCFile.h>

char writedata[40] = {0};
char readdata[40] = {0};
unsigned char sysTime = 0;

void setup()
{
    Serial.begin(115200);
    Serial.print("CFile test.\r\n");
	
    LFile.Create("file1.txt");
    LFile.Create("file2.txt");
	
    LFile.Write("file1.txt", "file1.txt\r\n");
    LFile.Write("file2.txt", "file2.txt\r\n");
	
    LFile.Read("file1.txt", readdata, 40, 0);
    Serial.print(readdata);
    Serial.print("\r\n");
}

void loop()
{
    unsigned char i = 10;
    unsigned long size = 0; 
	
    sprintf((char*)writedata, "It is time %d,Pls check!\r\n", sysTime ++);
    Serial.print(writedata);
    LFile.Write("file1.txt", writedata);
	
    LFile.Size("file1.txt", &size);
    Serial.print("File1 size is ");
    Serial.println(size);
	
    while(i--)
    {
        if(task_uart_key() == 1)
        {
            LFile.Delete("file2.txt");
            Serial.print("FileDelete.\r\n");
        }
        delay(100);
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
