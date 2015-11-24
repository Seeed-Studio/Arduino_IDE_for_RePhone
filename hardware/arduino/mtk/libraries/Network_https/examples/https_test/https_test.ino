
#include <Lhttps.h>


#define TEST_URL "https://www.howsmyssl.com/a/check"


char *buffer;

void setup(void)
{
  Serial.begin(115200);
  while(!Serial.available()); 
  Serial.print("https test.\r\n");
  Serial.flush();
  
  https.get_handle(print_url);
  https.connect(TEST_URL);
}

void loop(void)
{
  while(!Serial.available()); 
  Serial.flush();
  https.connect(TEST_URL);
}

void print_url(char *content, unsigned long len)
{
  Serial.print(content);
}

