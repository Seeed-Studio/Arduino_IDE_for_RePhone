
#include <LCheckSIM.h>
#include <LGSM.h>

char * text = "Hi,sms send test ok.";
char num[20] = "15915323285";
char buf_contex[200];

void setup() 
{    
    Serial1.begin(115200);
    Serial1.print("\r\n");  
    Serial1.println("SMS test");
    
    while(!LSMS.ready())
    {
        delay(1000);
    }
    Serial1.println("SMS ready is ok");
    
    LSMS.beginSMS(num);
    LSMS.print(text);
    
    if(LSMS.endSMS())
    {
        Serial1.println("SMS is sent");
    }
    else
    {
        Serial1.println("SMS send fail");
    } 
    
}

void loop() 
{   
    sms_test();
    Serial1.println("loop.");
    delay(1000);
}

void sms_test()
{
    if(!LSMS.available())
    {
         Serial1.println("No New SMS");
         return;   
    }

    Serial1.println("Get new sms: ");

    LSMS.remoteNumber(num, 20);         // display Number part
    //LSMS.remoteNumber(num, 20);         // display Number part
    Serial1.print("Number:");
    Serial1.println(num);
    
    LSMS.remoteContent(buf_contex, 50);
    //LSMS.remoteNumber(num, 20);         // display Number part
    Serial1.print("Content:");           // display Content part
    Serial1.println(buf_contex);

    if(buf_contex[0]=='T')
    {
        while(!LSMS.ready())
        {
            delay(1000);
        }
       
        Serial1.println("SIM ready for work!");
        LSMS.beginSMS(num);
        LSMS.print(text);
        
        if(LSMS.endSMS())
        {
            Serial1.println("SMS is sent");
        }
        else
        {
            Serial1.println("SMS send fail");
        } 
        LSMS.flush();  
    }
}
