

#ifndef _DISPLAY_H
#define _DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif


boolean lcd_init(void* user_data);
boolean lcd_font_init(void* user_data);
boolean lcd_back_light_level(void* user_data);
boolean lcd_screen_set(void* user_data);
boolean lcd_draw_font(void* user_data);
boolean lcd_draw_number(void* user_data);
boolean lcd_draw_point(void* user_data);
boolean lcd_draw_line(void* user_data);
boolean lcd_draw_fill_rectangle(void* user_data);
boolean lcd_draw_updata(void* user_data);

typedef struct
{
    VMUINT8 ulX;
	VMUINT8 ulY;
    VMCHAR *str;
	VMUINT32 BCulValue;
	VMUINT32 FCulValue;
	VMUINT8 ulSize;
}string_info_struct;

typedef struct
{
    VMUINT8 ulX;
	VMUINT8 ulY;
    VMUINT32 ulData;
	VMUINT32 BCulValue;
	VMUINT32 FCulValue;
	VMUINT8 ulSize;
}number_info_struct;

typedef struct
{
    VMUINT8 ulX;
	VMUINT8 ulY;
	VMUINT32 PCulValue;
}point_info_struct;

typedef struct
{
    VMUINT8 ulX1;
	VMUINT8 ulY1;
	VMUINT8 ulX2;
	VMUINT8 ulY2;
	VMUINT32 LCulValue;
}line_info_struct;

typedef struct
{
    VMUINT8 ulX1;
	VMUINT8 ulY1;
	VMUINT8 ulX2;
	VMUINT8 ulY2;
	VMUINT32 FCulValue;
}fill_info_struct;


#ifdef __cplusplus
}
#endif

#endif