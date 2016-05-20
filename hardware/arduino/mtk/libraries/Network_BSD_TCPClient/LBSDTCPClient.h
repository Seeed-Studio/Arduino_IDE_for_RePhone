
#ifndef _L_BSD_TCP_CLIENT_H_
#define _L_BSD_TCP_CLIENT_H_

#include "LTask.h"


class LBSDTCPClientClass : public _LTaskClass
{
public:
    LBSDTCPClientClass() {};
    
public:
    void connect(char *address);
    void request(char *request);
    void get_handle(void(*callback)(char *, long));

private:

};

extern LBSDTCPClientClass tcpClinent;


#endif