
#include "arduino.h"
#include "spi_dirver.h"
#include "LSPI.h"


extern unsigned char *g_spi_w_data;
extern unsigned char *g_spi_r_data;


void LSPIClass::begin(unsigned char bit, unsigned char mode, unsigned char divider)
{
    conf_struct conf_data;
    conf_data.Bit = bit;
    conf_data.Mode = mode;
    conf_data.Divider = divider;
    
	remoteCall(spi_begin, &conf_data);
}

unsigned char LSPIClass::transfer(unsigned char data)
{
	remoteCall(spi_transfer, &data);
	return *g_spi_r_data;
}

void LSPIClass::end(void)
{
	remoteCall(spi_end, NULL);
}


LSPIClass LSPI;

