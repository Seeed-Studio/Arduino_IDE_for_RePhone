
#include "arduino.h"
#include "vmdcl_spi.h"
#include "vmmemory.h"
#include "spi_dirver.h"


VM_DCL_HANDLE g_spi_handle = VM_DCL_HANDLE_INVALID;
unsigned char *g_spi_w_data;
unsigned char *g_spi_r_data;


boolean spi_begin(void* user_data)
{
    conf_struct *conf = (conf_struct *)user_data;
	VM_DCL_STATUS status;
	VM_DCL_HANDLE gpio_handle;
	vm_dcl_spi_config_parameter_t conf_data;

	/* SPI_MISO gpio config */
	gpio_handle = vm_dcl_open(VM_DCL_GPIO, 29);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_4, NULL);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_PULL_HIGH, NULL);
	
	/* SPI_MOSI gpio config */
	gpio_handle = vm_dcl_open(VM_DCL_GPIO, 28);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_4, NULL);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_PULL_HIGH, NULL);

	/* SPI_SCL gpio config */
	gpio_handle = vm_dcl_open(VM_DCL_GPIO, 27);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_MODE_4, NULL);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_ENABLE_PULL, NULL);
	vm_dcl_control(gpio_handle, VM_DCL_GPIO_COMMAND_SET_PULL_HIGH, NULL);

	if (VM_DCL_HANDLE_INVALID == g_spi_handle)
	g_spi_handle = vm_dcl_open(VM_DCL_SPI_PORT1, 0);

	if (VM_DCL_HANDLE_INVALID == g_spi_handle)
	return true;

    if(conf -> Divider == SPI_CLOCK_DIV2)
    {
        conf_data.clock_high_time = 1;
  	    conf_data.clock_low_time = 1;
    }
    else if(conf -> Divider == SPI_CLOCK_DIV4)
    {
        conf_data.clock_high_time = 3;
  	    conf_data.clock_low_time = 3;
    }
    else if(conf -> Divider == SPI_CLOCK_DIV8)
    {
        conf_data.clock_high_time = 7;
  	    conf_data.clock_low_time = 7;
    }
    else if(conf -> Divider == SPI_CLOCK_DIV16)
    {
        conf_data.clock_high_time = 15;
  	    conf_data.clock_low_time = 15;
    }
    else if(conf -> Divider == SPI_CLOCK_DIV32)
    {
        conf_data.clock_high_time = 31;
  	    conf_data.clock_low_time = 31;
    }
    else if(conf -> Divider == SPI_CLOCK_DIV64)
    {
        conf_data.clock_high_time = 63;
  	    conf_data.clock_low_time = 63;
    }
    else if(conf -> Divider == SPI_CLOCK_DIV128)
    {
        conf_data.clock_high_time = 127;
  	    conf_data.clock_low_time = 127;
    }
    else
    {
        return true;
    }
    
	conf_data.cs_hold_time = 15;
	conf_data.cs_idle_time = 15;
	conf_data.cs_setup_time= 15;
    
    if(conf -> Mode == SPI_MODE0)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_0;
        conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_0;
    }
    else if(conf -> Mode == SPI_MODE1)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_0;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_1;
    }
    else if(conf -> Mode == SPI_MODE2)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_1;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_0;
    }  
    else if(conf -> Mode == SPI_MODE3)
    {
        conf_data.clock_polarity = VM_DCL_SPI_CLOCK_POLARITY_1;
  	    conf_data.clock_phase = VM_DCL_SPI_CLOCK_PHASE_1;
    }
    else
    {
        return true;
    }
    
    if(conf -> Bit == SPI_ENDIAN_BIG)
    {
        conf_data.rx_endian = VM_DCL_SPI_ENDIAN_BIG;
        conf_data.tx_endian = VM_DCL_SPI_ENDIAN_BIG;
    }
    else if(conf -> Bit == SPI_ENDIAN_LITTLE)
    {
        conf_data.rx_endian = VM_DCL_SPI_ENDIAN_LITTLE;
        conf_data.tx_endian = VM_DCL_SPI_ENDIAN_LITTLE;
    }
    else
    {
        return true;
    }
    
	conf_data.rx_msbf = VM_DCL_SPI_MSB_FIRST;
	conf_data.tx_msbf = VM_DCL_SPI_MSB_FIRST;

	status = vm_dcl_control(g_spi_handle,VM_DCL_SPI_CONTROL_SET_CONFIG_PARAMETER,(void *)&conf_data);
	
	g_spi_w_data = (unsigned char *)vm_malloc_dma(2);
	g_spi_r_data = (unsigned char *)vm_malloc_dma(2);
	
	return true;
}

boolean spi_transfer(void* user_data)
{
	unsigned char *data = (unsigned char *)user_data;
	
	vm_dcl_spi_control_read_write_t write_and_read;
	VM_DCL_STATUS status;

	*g_spi_w_data = *data;
	write_and_read.read_data_ptr = (VMUINT8*)g_spi_r_data;
	write_and_read.read_data_length = 1;
	write_and_read.write_data_ptr = (VMUINT8*)g_spi_w_data;
	write_and_read.write_data_length = 1;

	status = vm_dcl_control(g_spi_handle,VM_DCL_SPI_CONTROL_WRITE_AND_READ,(void *)&write_and_read);
	
	return true;
}

boolean spi_end(void* user_data)
{
	vm_dcl_close(g_spi_handle);
    vm_free(g_spi_w_data);
	vm_free(g_spi_r_data);
	g_spi_handle = VM_DCL_HANDLE_INVALID;
}
