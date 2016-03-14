
#include <LCheckSIM.h>
#include <LGSM.h>

char * text = "Hi,sms send test ok.";
char num[20] = "15915323285";
char buf_contex[200];

void setup() 
{    
    Serial.begin(115200);
    Serial.print("\r\n");  
    Serial.println("SMS test");
    
    while(!LSMS.ready())
    {
        delay(1000);
    }
    Serial.println("SMS ready is ok");
    
    LSMS.beginSMS(num);
    LSMS.print(text);
    
    if(LSMS.endSMS())
    {
        Serial.println("SMS is sent");
    }
    else
    {
        Serial.println("SMS send fail");
    } 
    
}

void loop() 
{   
    sms_test();
    Serial.println("loop.");
    delay(1000);
}

void sms_test()
{
    if(!LSMS.available())
    {
         Serial.println("No New SMS");
         return;   
    }

    Serial.println("Get new sms: ");

    LSMS.remoteNumber(num, 20);         // display Number part
    //LSMS.remoteNumber(num, 20);         // display Number part
    Serial.print("Number:");
    Serial.println(num);
    
    LSMS.remoteContent(buf_contex, 50);
    //LSMS.remoteNumber(num, 20);         // display Number part
    Serial.print("Content:");           // display Content part
    Serial.println(buf_contex);

    if(buf_contex[0]=='T')
    {
        while(!LSMS.ready())
        {
            delay(1000);
        }
       
        Serial.println("SIM ready for work!");
        LSMS.beginSMS(num);
        LSMS.print(text);
        
        if(LSMS.endSMS())
        {
            Serial.println("SMS is sent");
        }
        else
        {
            Serial.println("SMS send fail");
        } 
        LSMS.flush();  
    }
}
