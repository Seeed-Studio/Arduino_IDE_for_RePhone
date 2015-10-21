void nfc_test()
{
    switch(task_uart_key())
    {
    	case 1:
    	LNFC.adapter_init();
    	Serial1.print("NFC adapter init.\r\n");
    	break;
    	
    	case 2:
    	str = LNFC.adapter_get_uid();
    	sprintf(buffer, "NFC uid is %x %x %x %x\r\n", str[2],str[3],str[4],str[5]);
    	Serial1.print(buffer);
    	break;
    	
    	case 3:
    	str = LNFC.adapter_read();
    	sprintf(buffer, "NFC read message is %s\r\n", str);
    	Serial1.print(buffer);
    	break;
    	
    	case 4:
    	sprintf(buffer, "Number is %d.\r\n", number++);
    	LNFC.adapter_write(buffer);
    	Serial1.print(buffer);
    	break;
    	
    	case 5:
    	LNFC.adapter_erase();
    	Serial1.print("NFC adapter erase.\r\n");
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
