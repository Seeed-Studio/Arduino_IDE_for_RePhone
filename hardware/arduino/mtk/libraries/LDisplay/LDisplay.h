

#ifndef _LDISPLAY_H
#define _LDISPLAY_H


#include "LTask.h"


class LDisplayClass : public _LTaskClass 
{
public:
    LDisplayClass() {};
	
public:
	/**
	 *  \brief Initialize the LCD hardware.  
	 *
	 *  \return Return Null.
	 */
	void init(void);
	
	/**
	 *  \brief Initialize the LCD font library.  
	 *
	 *  \return Return Null.
	 */
	void font_init(void);
	
	/**
	 *  \brief Set the level of LCD back light.  
	 *  
	 *  \param [in] ulValue the colour of back light, from 0 to 100
	 *  
	 *  \return Return Null.
	 */
	void back_light_level(uint8_t ulValue);
	
	/**
	 *  \brief Draw the colour of display.  
	 *  
	 *  \param [in] ulValue the colour of back light, format is R:G:B -> 255:255:255
	 *  
	 *  \return Return Null.
	 */
	void screen_set(uint32_t ulValue);
	
	/**
	 *  \brief Display font.  
	 *  
	 *  \param [in] ulX the x coordinate of font, from 0 to 239
	 *  \param [in] ulY the y coordinate of font, from 0 to 239
	 *  \param [in] str the pointer of font
	 *  \param [in] BGulValue the colour of back light, format is R:G:B -> 255:255:255
	 *  \param [in] DTulValue the colour of font, format is R:G:B -> 255:255:255
	 *	\param [in] ulSize the size of font
	 *  
	 *  \return Return Null.
	 */
	void draw_font(uint8_t ulX, uint8_t ulY, const char* str, uint32_t BGulValue, uint32_t DTulValue, uint8_t ulSize);
	
	/**
	 *  \brief Display number.  
	 *  
	 *  \param [in] ulX the x coordinate of font, from 0 to 239
	 *  \param [in] ulY the y coordinate of font, from 0 to 239
	 *  \param [in] ulData the number that want to display
	 *  \param [in] BCulValue the colour of back light, format is R:G:B -> 255:255:255
	 *  \param [in] FCulValue the colour of font, format is R:G:B -> 255:255:255
	 *	\param [in] ulSize the size of font
	 *  
	 *  \return Return Null.
	 */	
	void draw_number(uint8_t ulX, uint8_t ulY, uint32_t ulData, uint32_t BCulValue, uint32_t FCulValue, uint8_t ulSize);
	
	/**
	 *  \brief Draw point, need function draw_point to update display.
	 *  
	 *  \param [in] ulX x of the point, from 0 to 239
	 *  \param [in] ulY y of the point, from 0 to 239
	 *  \param [in] PCulValue the colour of point, format is R:G:B -> 255:255:255
	 *  
	 *  \return Return Null.
	 */	
	void draw_point(uint8_t ulX, uint8_t ulY, uint32_t PCulValue);
	
	/**
	 *  \brief Draw line, need function draw_point to update display.
	 *  
	 *  \param [in] ulX1 x of the start point, from 0 to 239
	 *  \param [in] ulY1 y of the start point, from 0 to 239
	 *  \param [in] ulX2 x of the end point, from 0 to 239
	 *  \param [in] ulY2 y of the end point, from 0 to 239
	 *  \param [in] LCulValue the colour of line, format is R:G:B -> 255:255:255
	 *  
	 *  \return Return Null.
	 */	
	void draw_line(uint8_t ulX1, uint8_t ulY1, uint8_t ulX2, uint8_t ulY2, uint32_t LCulValue);
	
	/**
	 *  \brief Draw fill rectangle, need function draw_point to update display.
	 *  
	 *  \param [in] ulX1 x offset of start point, from 0 to 239
	 *  \param [in] ulY1 y offset of start point, from 0 to 239
	 *  \param [in] ulX2 x offset of end point, from 0 to 239
	 *  \param [in] ulY2 y offset of end point, from 0 to 239
	 *  \param [in] FCulValue the colour of line, format is R:G:B -> 255:255:255
	 *  
	 *  \return Return Null.
	 */
	void draw_fill_rectangle(uint8_t ulX1, uint8_t ulY1, uint8_t ulX2, uint8_t ulY2, uint32_t FCulValue);
	
	/**
	 *  \brief Update to display.
	 *   
	 *  \return Return Null.
	 */
	void draw_updata(void);
	
private:
	
};

extern LDisplayClass Lcd;


#endif