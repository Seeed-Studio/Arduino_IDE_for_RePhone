
#ifndef __LGTOUCH_H__
#define __LGTOUCH_H__


#include "LTask.h"


class LTouchClass : public _LTaskClass
{
public:
    LTouchClass() {};
	
public:
	/**
	 *  \brief Initialize the touch hardware.  
	 *
	 *  \return Return Null.
	 */
	void Init(void);
	
	/**
	 *  \brief Check the event of touch.  
	 *
	 *  \return Return 1 or 0. 1 there is a touch event, 0 there is not.
	 */
	char Event_available(void);
	
	/**
	 *  \brief Get the data of touch.  
	 *  
	 *  \param [in] event the pointer of touch event
	 *  \param [in] x the pointer of touch x value
	 *  \param [in] y the pointer of touch y value
	 *  
	 *  \return Return Null.
	 */
	void Get_event_xy(char *event, int *x, int *y);
	
	/**
	 *  \brief Set the handle of touch event.  
	 *  
	 *  \param [in] callback the function of touch event call back.
	 *  
	 *  \return Return Null.
	 */
	void Event_handle(void(*callback)(char, int, int));
	
private:
	
};

extern LTouchClass Tp;


#endif