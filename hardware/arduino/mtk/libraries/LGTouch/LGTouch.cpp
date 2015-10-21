
#include "LGTouch.h"
#include "GTouch.h"
	

void LTouchClass::Init(void)
{
	remoteCall(tp_init, NULL);
}

char LTouchClass::Event_available(void)
{
	char data;
	remoteCall(tp_event_available, &data);
	return data;
}

void LTouchClass::Get_event_xy(char *event, int *x, int *y)
{
	event_xy_info_struct data;
	remoteCall(tp_get_event_xy, &data);
	*event = data.ulEvent;
	*x = data.ulX;
	*y = data.ulY;
	tp_event_clean(NULL);
}

void LTouchClass::Event_handle(void(*callback)(char, int, int))
{
	tp_set_handle(callback);
}

LTouchClass Tp;