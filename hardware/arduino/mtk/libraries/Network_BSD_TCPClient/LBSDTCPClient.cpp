
#include "LBSDTCPClient.h"
#include "BSDTCPClient.h"


void LBSDTCPClientClass::connect(char* address)
{
    remoteCall(BSD_TCP_client_connect, address);
}

void LBSDTCPClientClass::request(char* request)
{
    remoteCall(BSD_TCP_client_request, request);
}

void LBSDTCPClientClass::get_handle(void(*callback)(char *, long))
{
    BSD_TCP_client_set_new_event_callback(callback);
}


LBSDTCPClientClass tcpClinent;
