
#include <LBSDTCPClient.h>


#define TEST_ADDR "180.149.132.47"
#define TEST_REQU "GET http://www.baidu.com/ HTTP/1.1\r\nHOST:www.baidu.com\r\n\r\n"


char *buffer;


void setup(void)
{
  Serial.begin(115200);
  while(!Serial.available()); 
  Serial.print("BSD TCP Client test.\r\n");
  Serial.flush();
  
  tcpClinent.get_handle(print_url);
  tcpClinent.connect((char *)TEST_ADDR);
  tcpClinent.request((char *)TEST_REQU);
}

void loop(void)
{
  while(!Serial.available()); 
  Serial.flush();
  tcpClinent.request((char *)TEST_REQU);
}

void print_url(char *content, long len)
{
  Serial.println("content length is ");
  Serial.println(len);
  Serial.println("content is ");
  Serial.print(content);
}

