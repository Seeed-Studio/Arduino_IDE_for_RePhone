

#include "LDisplay.h"
#include "Display.h"


void LDisplayClass::init(void)
{
	remoteCall(lcd_init, NULL);
}

void LDisplayClass::font_init(void)
{
	remoteCall(lcd_font_init, NULL);
}

void LDisplayClass::back_light_level(uint8_t ulValue)
{
	remoteCall(lcd_back_light_level, &ulValue);
}

void LDisplayClass::screen_set(uint32_t ulValue)
{
	remoteCall(lcd_screen_set, &ulValue);
}

void LDisplayClass::draw_font(uint8_t ulX, uint8_t ulY, const char* str, uint32_t BCulValue, uint32_t FCulValue, uint8_t ulSize)
{
	string_info_struct data;
	data.ulX = ulX;
	data.ulY = ulY;
	data.str = (VMCHAR*)str;
	data.BCulValue = BCulValue;
	data.FCulValue = FCulValue;
	data.ulSize = ulSize;
	remoteCall(lcd_draw_font, &data);
}

void LDisplayClass::draw_number(uint8_t ulX, uint8_t ulY, uint32_t ulData, uint32_t BCulValue, uint32_t FCulValue, uint8_t ulSize)
{
	number_info_struct data;	
	data.ulX = ulX;
	data.ulY = ulY;
	data.ulData = ulData;
	data.BCulValue = BCulValue;
	data.FCulValue = FCulValue;
	data.ulSize = ulSize;
	remoteCall(lcd_draw_number, &data);
}

void LDisplayClass::draw_point(uint8_t ulX, uint8_t ulY, uint32_t PCulValue)
{
	point_info_struct data;	
	data.ulX = ulX;
	data.ulY = ulY;
	data.PCulValue = PCulValue;
	remoteCall(lcd_draw_point, &data);
}

void LDisplayClass::draw_line(uint8_t ulX1, uint8_t ulY1, uint8_t ulX2, uint8_t ulY2, uint32_t LCulValue)
{
	line_info_struct data;	
	data.ulX1 = ulX1;
	data.ulY1 = ulY1;
	data.ulX2 = ulX2;
	data.ulY2 = ulY2;
	data.LCulValue = LCulValue;
	remoteCall(lcd_draw_line, &data);
}

void LDisplayClass::draw_fill_rectangle(uint8_t ulX1, uint8_t ulY1, uint8_t ulX2, uint8_t ulY2, uint32_t FCulValue)
{
	fill_info_struct data;	
	data.ulX1 = ulX1;
	data.ulY1 = ulY1;
	data.ulX2 = ulX2;
	data.ulY2 = ulY2;
	data.FCulValue = FCulValue;
	remoteCall(lcd_draw_fill_rectangle, &data);
}

void LDisplayClass::draw_updata(void)
{
	remoteCall(lcd_draw_updata, NULL);
}

LDisplayClass Lcd;