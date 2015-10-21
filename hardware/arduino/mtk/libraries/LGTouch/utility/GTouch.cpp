

#include "Arduino.h"
#include "vmdcl.h"
#include "vmlog.h"
#include "vmtype.h"
#include "vmsystem.h"
#include "vmdrv_tp.h"
#include "GTouch.h"
#include "tp_goodix_gt9xx.h"


char tp_flag = 0;
char tp_event = 0;
int tp_x = 0;
int tp_y = 0; 


void tp_event_handle(char event, int x, int y)
{
	tp_flag = 1;
	tp_event = event;
	tp_x = x;
	tp_y = y;
}

boolean tp_init(void* user_data)
{
	tp_gt9xx_init();
	tp_set_handle(tp_event_handle);
	return true;
}

boolean tp_event_available(void* user_data)
{
	char *data = (char *)user_data;
	*data = tp_flag;
	return true;
}

boolean tp_get_event_xy(void* user_data)
{
	event_xy_info_struct* data = (event_xy_info_struct*)user_data;

	data->ulEvent = tp_event;
	data->ulX = tp_x;
	data->ulY = tp_y;
	return true;
}

boolean tp_event_clean(void* user_data)
{
	tp_flag = 0;
	return true;
}

boolean tp_set_handle(void(*callback)(char, int, int))
{
	tp_set_new_event_callback(callback);
	return true;
}