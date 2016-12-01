

#include "Arduino.h"
#include "vmdcl.h"
#include "vmlog.h"
#include "vmsystem.h"
#include "vmfirmware.h"
#include "vmmemory.h"
#include "vmchset.h"
#include "vmgraphic.h"
#include "vmgraphic_font.h"
#include "vmdcl_pwm.h"
#include "Display.h"
#include "lcd_sitronix_st7789s.h"


#define LCD_GPIO_LIGHT 3


vm_graphic_frame_t g_frame;
vm_graphic_frame_t g_rotated_frame;
const vm_graphic_frame_t* g_frame_blt_group[1];


boolean lcd_back_light_level(void* user_data) 
{
	VMUINT8* ulValue = (VMUINT8*)user_data;
    
	VM_DCL_HANDLE pwm_handle;
    vm_dcl_pwm_set_clock_t pwm_clock;
    vm_dcl_pwm_set_counter_threshold_t pwm_config_adv;

	pwm_handle = vm_dcl_open(VM_DCL_GPIO,LCD_GPIO_LIGHT);
	vm_dcl_control(pwm_handle,VM_DCL_GPIO_COMMAND_SET_MODE_4,NULL);
	vm_dcl_close(pwm_handle); 
	
    pwm_handle = vm_dcl_open(VM_DCL_PWM_4, vm_dcl_get_owner_id());
    vm_dcl_control(pwm_handle, VM_PWM_CMD_START, 0);
	
    pwm_config_adv.counter = 100;
    pwm_config_adv.threshold = *ulValue;
    pwm_clock.source_clock = 0;
    pwm_clock.source_clock_division = 3;
    vm_dcl_control(pwm_handle, VM_PWM_CMD_SET_CLOCK, (void *) (&pwm_clock));
    vm_dcl_control(pwm_handle, VM_PWM_CMD_SET_COUNTER_AND_THRESHOLD, (void *) (&pwm_config_adv));
    vm_dcl_close(pwm_handle);
    
	return true;
}

boolean lcd_init(void* user_data)
{
	lcd_st7789s_init();
    
	return true;
}

boolean lcd_font_init(void* user_data)
{
	VM_RESULT result;
    VMUINT32 pool_size;
	VMUINT8* g_font_pool;
    result = vm_graphic_get_font_pool_size(0, 0, 0, &pool_size);
	
    if(VM_IS_SUCCEEDED(result)){
        g_font_pool = (VMUINT8*)vm_malloc(pool_size);
        if(NULL != g_font_pool){
            vm_graphic_init_font_pool(g_font_pool, pool_size);
        }else{
            vm_log_info("allocate font pool memory failed, pool size: %d", pool_size);
        }
    }else{
        vm_log_info("get font pool size failed, result:%d", result);
    }
	
	g_frame.width = 240;
    g_frame.height = 240;
    g_frame.color_format = VM_GRAPHIC_COLOR_FORMAT_16_BIT;
    g_frame.buffer = (VMUINT8*)vm_malloc_dma(g_frame.width * g_frame.height * 2);
    g_frame.buffer_length = (g_frame.width * g_frame.height * 2);
	
	g_rotated_frame.width = 240;
    g_rotated_frame.height = 240;
    g_rotated_frame.color_format = VM_GRAPHIC_COLOR_FORMAT_16_BIT;
    g_rotated_frame.buffer = (VMUINT8*)vm_malloc_dma(g_rotated_frame.width * g_rotated_frame.height * 2);
    g_rotated_frame.buffer_length = (g_rotated_frame.width * g_rotated_frame.height * 2);
	
	//g_frame_blt_group[0] = &g_frame;
    g_frame_blt_group[0] = &g_rotated_frame;
	
	return true;
}

boolean lcd_screen_set(void* user_data)
{
	VMUINT32* ulValue = (VMUINT32*)user_data;
    vm_graphic_color_argb_t color;		// use to set screen and text color
    //vm_graphic_point_t frame_position[1] = {0, 0};

    // set color and draw back ground
    color.a = 255;
    color.r = (((*ulValue) >> 16) & 0xff);
    color.g = (((*ulValue) >> 8) & 0xff);
    color.b = ((*ulValue) & 0xff);
    vm_graphic_set_color(color);
    vm_graphic_draw_solid_rectangle(&g_frame, 0,0, 240,240);
	
	//vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
    //vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);

	return true;
}

boolean lcd_draw_font(void* user_data)
{
	string_info_struct* data = (string_info_struct*) user_data;
	
	VMCHAR s[52];					    // string's buffer
    vm_graphic_color_argb_t color;		// use to set screen and text color
    //vm_graphic_point_t frame_position[1] = {0, 0};

    vm_chset_ascii_to_ucs2((VMWSTR)s,52, data->str);
    
	// set color and draw back ground
    color.a = 0;
    color.r = ((data->BCulValue >> 16) & 0xff);
	color.g = ((data->BCulValue >> 8) & 0xff);
	color.b = (data->BCulValue & 0xff);
    vm_graphic_set_color(color);
    vm_graphic_set_font_size(data->ulSize);
    vm_graphic_draw_solid_rectangle(&g_frame, data->ulX, data->ulY, vm_graphic_get_text_width((VMWSTR)s), vm_graphic_get_text_height((VMWSTR)s));

	// set color and draw text
    color.a = 0;
    color.r = ((data->FCulValue >> 16) & 0xff);
	color.g = ((data->FCulValue >> 8) & 0xff);
	color.b = (data->FCulValue & 0xff);
    vm_graphic_set_color(color);
    vm_graphic_draw_text(&g_frame,data->ulX, data->ulY, (VMWSTR)s);
	
	//vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
    //vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);
	
	return true;
}

boolean lcd_draw_number(void* user_data)
{
	number_info_struct* data = (number_info_struct*) user_data;
	VMCHAR s[26];					    // string's buffer
    vm_graphic_color_argb_t color;		// use to set screen and text color
    //vm_graphic_point_t frame_position[1] = {0, 0};

    VMCHAR str[13]={0};
    sprintf((char *)str, "%d", data->ulData);
    
    vm_chset_ascii_to_ucs2((VMWSTR)s,26, str);
   
	// set color and draw back ground
    color.a = 0;
    color.r = ((data->BCulValue >> 16) & 0xff);
	color.g = ((data->BCulValue >> 8) & 0xff);
	color.b = (data->BCulValue & 0xff);
    vm_graphic_set_color(color);
    vm_graphic_set_font_size(data->ulSize); 
    vm_graphic_draw_solid_rectangle(&g_frame, data->ulX, data->ulY, vm_graphic_get_text_width((VMWSTR)s), vm_graphic_get_text_height((VMWSTR)s));
    
	// set color and draw text
    color.a = 0;
    color.r = ((data->FCulValue >> 16) & 0xff);
	color.g = ((data->FCulValue >> 8) & 0xff);
	color.b = (data->FCulValue & 0xff);
    vm_graphic_set_color(color);
    vm_graphic_draw_text(&g_frame,data->ulX, data->ulY, (VMWSTR)s);
	
	//vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
    //vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);
	
	return true;
}

boolean lcd_draw_point(void* user_data)
{
	point_info_struct* data = (point_info_struct*) user_data;
	//vm_graphic_point_t frame_position[1] = {0, 0};
	/*
    vm_graphic_color_argb_t color;
    color.a = 0;
    color.r = ((data->PCulValue >> 16) & 0xff);
	color.g = ((data->PCulValue >> 8) & 0xff);
	color.b = (data->PCulValue & 0xff);
    vm_graphic_set_color(color);
    vm_graphic_draw_point(&g_frame, data->ulX, data->ulY);
	*/
	VMUINT16 *pbuf = (VMUINT16 *)g_frame.buffer; 
    pbuf += data->ulY * 240 + data->ulX;
    *pbuf = ((data->PCulValue >> 8) & (0x1F << 11)) | ((data->PCulValue >> 5) & (0x3F << 5)) | ((data->PCulValue >> 3) & 0x1F);
	
	//vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
	//vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);
	
	return true;
}

boolean lcd_draw_line(void* user_data)
{
	line_info_struct* data = (line_info_struct*) user_data;
	vm_graphic_color_argb_t color;
	//vm_graphic_point_t frame_position[1] = {0, 0};

    color.a = 0;
    color.r = ((data->LCulValue >> 16) & 0xff);
	color.g = ((data->LCulValue >> 8) & 0xff);
	color.b = (data->LCulValue & 0xff);
	
    vm_graphic_set_color(color);
    vm_graphic_draw_line(&g_frame, data->ulX1, data->ulY1, data->ulX2, data->ulY2);
	
	//vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
	//vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);
	
	return true;
}

boolean lcd_draw_fill_rectangle(void* user_data)
{
	fill_info_struct* data = (fill_info_struct*) user_data;
	vm_graphic_color_argb_t color;
	//vm_graphic_point_t frame_position[1] = {0, 0};

    color.a = 0;
    color.r = ((data->FCulValue >> 16) & 0xff);
	color.g = ((data->FCulValue >> 8) & 0xff);
	color.b = (data->FCulValue & 0xff);
	
    vm_graphic_set_color(color);
    vm_graphic_draw_solid_rectangle(&g_frame, data->ulX1, data->ulY1, data->ulX2 - data->ulX1, data->ulY2 - data->ulY1);
	
	//vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
	//vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);
	
	return true;
}

boolean lcd_draw_updata(void* user_data)
{
	vm_graphic_point_t frame_position[1] = {0, 0};
	vm_graphic_rotate_frame(&g_rotated_frame, &g_frame, VM_GRAPHIC_ROTATE_180);
	vm_graphic_blt_frame(g_frame_blt_group, frame_position, (VMINT)1);
    
	return true;
}