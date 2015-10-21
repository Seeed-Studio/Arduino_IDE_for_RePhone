
#include <LCheckSIM.h>
#include <LGSM.h>

char *charbuffer = "075510086";
char num[20] = {0};

void setup() 
{
    Serial1.begin(115200);
    Serial1.print("\r\n");
    //LVoiceCall.hangCall();
    Serial1.print("Voice Call Test\r\n");
}

void loop() 
{   
    unsigned KeyValue = 0;
    KeyValue = task_uart_key();
    
    if(KeyValue == 1)
    {
        KeyValue = 0;
        if(LCheckSIM.isCheck() == 1) 
        {
              Serial1.print("Voice call begin.\r\n");
              LVoiceCall.voiceCall(charbuffer);
              
              while(1)
              {
                      KeyValue = task_uart_key();
                      
                      if(KeyValue == 2)
                      {
                          KeyValue = 0;
                          LVoiceCall.hangCall();
                          Serial1.print("Hang call.\r\n");
                          break;
                      }
                      if(LVoiceCall.getVoiceCallStatus() == IDLE_CALL)break;
                      delay(50);
              }
        }
        else
        {
            Serial1.print("No SIM.\r\n");
        }
    }
    
    if(LVoiceCall.getVoiceCallStatus() == RECEIVINGCALL)
    {  
        Serial1.print("Call come in.\r\n");
        LVoiceCall.retrieveCallingNumber(num,20);
        Serial1.print("Number is ");
        Serial1.println(num);
        LVoiceCall.answerCall();
        while(1)
        {
            KeyValue = task_uart_key();
            
            if(KeyValue == 2)
            {
                KeyValue = 0;
                LVoiceCall.hangCall();
                Serial1.print("Hang call.\r\n");
                break;
            }
            if(LVoiceCall.getVoiceCallStatus() == IDLE_CALL)break;
            delay(50);
        }
    }
    delay(50);
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

/*
#include <LGSM.h>

String remoteNumber = "";  // the number you will call
char charbuffer[20];

void setup()
{
  // initialize serial communications
  Serial1.begin(115200); 
  Serial1.println("Make Voice Call");
  Serial1.println("Enter phone number to call.");
}

void loop()
{
  // add any incoming characters to the String:
  while (Serial1.available() > 0)
  {
    char inChar = Serial1.read();
    // if it's a newline, that means you should make the call:
    if (inChar == '\n')
    {
      // make sure the phone number is not too long:
      if (remoteNumber.length() < 20)
      {
        // let the user know you're calling:
        Serial1.print("Calling to : ");
        Serial1.println(remoteNumber);
        Serial1.println();

        // Call the remote number
        remoteNumber.toCharArray(charbuffer, 20);
        
        // Check if the receiving end has picked up the call
        if(LVoiceCall.voiceCall(charbuffer))
        {
          Serial1.println("Call Established. Enter line to end");
          // Wait for some input from the line
          while(Serial1.read() !='\n');
          // And hang up
          LVoiceCall.hangCall();
        }
        Serial1.println("Call Finished");
        remoteNumber="";
        Serial1.println("Enter phone number to call.");
      } 
      else
      {
        Serial1.println("That's too long for a phone number. I'm forgetting it"); 
        remoteNumber = "";
      }
    } 
    else
    {
      // add the latest character to the message to send:
      if(inChar!='\r')
        remoteNumber += inChar;
    }
  } 
}
*/
/*
#include <LGSM.h>

char numtel[20];           // buffer for the incoming call

void setup()
{
  // initialize serial communications
  Serial1.begin(115200);
  Serial1.println("Receive Voice Call");

  // This makes sure the modem notifies correctly incoming events
  LVoiceCall.hangCall();

  Serial1.println("Waiting Call");
}

void loop()
{
  // Check the status of the voice call
  switch (LVoiceCall.getVoiceCallStatus()) 
  {
    case IDLE_CALL: // Nothing is happening
    Serial1.println("IDLE_CALL");
    break;

    case CALLING: // This should never happen, as we are not placing a call
    Serial1.println("CALLING");
    break;

    case RECEIVINGCALL: // Yes! Someone is calling us
    Serial1.println("RECEIVING CALL");
    // Retrieve the calling number
    LVoiceCall.retrieveCallingNumber(numtel, 20);
    // Print the calling number
    Serial1.print("Number:");
    Serial1.println(numtel);
    // Answer the call, establish the call
    LVoiceCall.answerCall();         
    break;

    case TALKING:  // In this case the call would be established
    Serial1.println("TALKING. Enter line to interrupt.");
    while(Serial1.read()!='\n')delay(100);
    LVoiceCall.hangCall();
    Serial1.println("HANG. Waiting Call.");      
    break;
    
    default:
    break;
  }
  delay(1000);
}
*/
