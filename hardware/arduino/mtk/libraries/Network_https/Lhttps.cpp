
#include "Lhttps.h"
#include "https.h"


void LHttpsClass::connect(char* url)
{
	remoteCall(https_connect, url);
}

void LHttpsClass::stop(void)
{
	remoteCall(https_stop, NULL);
}

void LHttpsClass::get_handle(void(*callback)(char *, unsigned long))
{
	https_set_new_event_callback(callback);
}

LHttpsClass https;
