

#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_


#ifdef __cplusplus
extern "C" {
#endif


#define SPI_ENDIAN_BIG 0x00
#define SPI_ENDIAN_LITTLE 0x01

// SPI clock is 1/4 of system clock
#define SPI_CLOCK_DIV4 0x00
// SPI clock is 1/16 of system clock
#define SPI_CLOCK_DIV16 0x01
// SPI clock is 1/64 of system clock
#define SPI_CLOCK_DIV64 0x02
// SPI clock is 1/128 of system clock
#define SPI_CLOCK_DIV128 0x03
// SPI clock is 1/2 of system clock
#define SPI_CLOCK_DIV2 0x04
// SPI clock is 1/8 of system clock
#define SPI_CLOCK_DIV8 0x05
// SPI clock is 1/32 of system clock
#define SPI_CLOCK_DIV32 0x06

// SPI data transfer mode 0
#define SPI_MODE0 0x02
// SPI data transfer mode 1
#define SPI_MODE1 0x00
// SPI data transfer mode 2
#define SPI_MODE2 0x03
// SPI data transfer mode 3
#define SPI_MODE3 0x01


typedef struct
{
    unsigned char Bit;
	unsigned char Mode;
	unsigned char Divider;
}conf_struct;


boolean spi_begin(void* user_data);
boolean spi_transfer(void* user_data);
boolean spi_end(void* user_data);


#ifdef __cplusplus
}
#endif

#endif

