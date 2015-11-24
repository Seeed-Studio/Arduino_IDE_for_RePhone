
#ifndef _LHTTPS_H
#define _LHTTPS_H

#include "LTask.h"


class LHttpsClass : public _LTaskClass 
{
public:
    LHttpsClass() {};
	
public:
	void connect(char* url);
	void get_handle(void(*callback)(char *, unsigned long));
	void stop(void);
	
private:
	int read_ok;
};

extern LHttpsClass https;


#endif