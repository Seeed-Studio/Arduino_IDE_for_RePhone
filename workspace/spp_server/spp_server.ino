
#include <LBT.h>
#include <LBTServer.h>
#define SPP_SVR "SPP_SERVER" // it is the server's visible name, customize it yourself.

void setup()
{
    bool success = LBTServer.begin((uint8_t*)SPP_SVR);
    if( !success )
    {
        delay(0xffffffff);
    }
    // waiting for Spp Client to connect
    bool connected = LBTServer.accept(1800);
    if( !connected )
    {
        delay(0xffffffff);
    }
}

void loop()
{
    char buffer[32] = {0};
    if(LBTServer.available())
    {
        int read_size = LBTServer.readBytes((uint8_t*)buffer, 32);
        char* buffer_w = "SPP Server.\r\n";
        //int write_size = LBTServer.write((uint8_t*)buffer_w, strlen(buffer_w));
        int write_size = LBTServer.write((uint8_t*)buffer, strlen(buffer));
    }
}
