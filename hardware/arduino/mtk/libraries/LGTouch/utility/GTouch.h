

#ifndef _GTOUCH_H
#define _GTOUCH_H

#ifdef __cplusplus
extern "C" {
#endif


void tp_event_handle(char event, int x, int y);
boolean tp_init(void* user_data);
boolean tp_event_available(void* user_data);
boolean tp_get_event_xy(void* user_data);
boolean tp_event_clean(void* user_data);
boolean tp_set_handle(void(*callback)(char, int, int));


typedef struct
{
	char ulEvent;
    int ulX;
	int ulY;
}event_xy_info_struct;


#ifdef __cplusplus
}
#endif

#endif