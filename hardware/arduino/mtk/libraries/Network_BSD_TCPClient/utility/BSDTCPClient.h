
#ifndef _BSD_TCP_CLIENT_H_
#define _BSD_TCP_CLIENT_H_


boolean BSD_TCP_client_connect(void* user_data);
boolean BSD_TCP_client_request(void* user_data);
boolean BSD_TCP_client_set_new_event_callback(void(*cb)(char *, long));


#endif