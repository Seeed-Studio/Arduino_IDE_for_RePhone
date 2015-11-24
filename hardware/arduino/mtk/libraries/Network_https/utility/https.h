
#ifndef _HTTPS_H
#define _HTTPS_H


boolean https_connect(void* user_data);
boolean https_stop(void* user_data);
boolean https_set_new_event_callback(void(*cb)(char *, unsigned long));


#endif
