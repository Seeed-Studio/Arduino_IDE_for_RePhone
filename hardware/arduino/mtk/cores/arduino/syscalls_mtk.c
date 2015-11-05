#include <stdio.h>
#if defined (  __GNUC__  ) /* GCC CS3 */
#include <sys/stat.h>
#endif
#include "vmtype.h"
#include "vmlog.h"
#include "vmmemory.h"
#include "vmdcl.h"
#include "vmdcl_gpio.h"
#include "vmdcl_pwm.h"

typedef VMINT (*vm_get_sym_entry_t)(char* symbol);
vm_get_sym_entry_t vm_get_sym_entry;

static unsigned int g_memory_size = 1024;
static void* g_base_address = NULL;

#define RESERVED_MEMORY_SIZE 500*1024


int __g_errno = 0;

 void __cxa_pure_virtual()
{
    while (1);
}

int * __errno()
{
	return &__g_errno;
}


extern caddr_t _sbrk ( int incr )
{
    static void* heap = NULL ;
    static void* base = NULL ;
    void* prev_heap ;

    if ( heap == NULL )
    {
        base = (unsigned char *)g_base_address; 
				if(base == NULL)
				{
					vm_log_fatal("malloc failed");
				}
				else
				{
					heap = base;
					vm_log_info("init memory success");
				}
    }
    
    if (heap + incr > g_base_address + g_memory_size) 
    {
        vm_log_fatal("memory not enough");
    }
    
    prev_heap = heap;

    heap += incr ;

    return (caddr_t) prev_heap ;
}

extern int link( char *cOld, char *cNew )
{
    return -1 ;
}

extern int _close( int file )
{
    return -1 ;
}

extern int _fstat( int file, struct stat *st )
{
    st->st_mode = S_IFCHR ;

    return 0 ;
}

extern int _isatty( int file )
{
    return 1 ;
}

extern int _lseek( int file, int ptr, int dir )
{
    return 0 ;
}

extern int _read(int file, char *ptr, int len)
{
    return 0 ;
}

extern int _write( int file, char *ptr, int len )
{
    return len ;
}

extern void _exit( int status )
{
    for ( ; ; ) ;
}

extern void _kill( int pid, int sig )
{
    return ;
}

extern int _getpid ( void )
{
    return -1 ;
}

int __cxa_guard_acquire(int *g) {return !*(char *)(g);};
void __cxa_guard_release (int *g) {*(char *)g = 1;};

typedef void (**__init_array) (void);

void __libc_init_array(void);

void gcc_entry(unsigned int entry, unsigned int init_array_start, unsigned int count) 
{
	unsigned int i;
	__init_array ptr;
	unsigned int size = 0;
	vm_get_sym_entry = (vm_get_sym_entry_t)entry;
	
	size = vm_pmng_get_total_heap_size();

#if defined(__LINKIT_ONE__)
 	 if(size > RESERVED_MEMORY_SIZE)
	 {
		g_memory_size = size - RESERVED_MEMORY_SIZE;		
 	 }
#endif

  g_base_address = vm_malloc(g_memory_size);

  ptr = (__init_array)init_array_start;
  for (i = 1; i < count; i++)
  {
  		ptr[i]();
  }
	vm_main();
}


#define VM_DCL_PIN_MODE_MAX 10

typedef struct{
   VMINT32 gpio;
   VMINT32 eint;
   VMINT32 adc;
   VMINT32 pwm;
   VMCHAR mux[VM_DCL_PIN_MODE_MAX];
}VM_DCL_PIN_MUX;

#if defined(__HDK_LINKIT_ONE_V1__)
#define VM_DCL_PIN_TABLE_SIZE 26
#elif defined(__HDK_LINKIT_ASSIST_2502__)
#define VM_DCL_PIN_TABLE_SIZE 15
#else
#define VM_DCL_PIN_TABLE_SIZE 1
#endif

#if defined(__HDK_LINKIT_ONE_V1__)
const VM_DCL_PIN_MUX pinTable[VM_DCL_PIN_TABLE_SIZE] = {
  {VM_PIN_D0, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_UART, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D1, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_UART, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D2, 20, 0, 0,  {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_PWM, VM_DCL_PIN_MODE_EINT, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D3, 11, 0, VM_DCL_PWM_1,  {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_EINT, VM_DCL_PIN_MODE_PWM , 0, 0, 0, 0, 0, 0}}, 
  {VM_PIN_D4, 0, 0, 0,  {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D5, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D6, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D7, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D8, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D9, 0, 0, VM_DCL_PWM_4,{VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_PWM, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D10, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, 0, 0}},
  {VM_PIN_D11, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, VM_DCL_PIN_MODE_SDIO, 0}},
  {VM_PIN_D12, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, VM_DCL_PIN_MODE_SDIO, 0}},
  {VM_PIN_D13, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, VM_DCL_PIN_MODE_SDIO, 0}},
  {VM_PIN_D14, 0, 12, 0, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D15, 0, 15, 0, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D16, 0, 13, 0, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D18, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_I2C, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_D19, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_I2C, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_A0, 0, 12, 0, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_A1, 0, 15, 0, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_A2, 0, 13, 0, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_SDA, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_I2C, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_SCL, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_I2C, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_RX, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_UART, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_TX, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_UART, 0, 0 , 0, 0, 0, 0, 0, 0}}
};      
#elif defined(__HDK_LINKIT_ASSIST_2502__)
static const VM_DCL_PIN_MUX pinTable[VM_DCL_PIN_TABLE_SIZE] = {
  {VM_PIN_P0, 11, 0, VM_DCL_PWM_1, {VM_DCL_PIN_MODE_GPIO, 0, VM_DCL_PIN_MODE_EINT, VM_DCL_PIN_MODE_PWM , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P1, 0, 0, VM_DCL_PWM_4, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_PWM, 0, 0, 0, 0, 0}},
  {VM_PIN_P2, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, 0, 0}},
  {VM_PIN_P3, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, 0, 0}},
  {VM_PIN_P4, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, 0, 0}},
  {VM_PIN_P5, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, 0, 0, 0 , VM_DCL_PIN_MODE_SPI, 0, 0, 0, 0, 0}},
  {VM_PIN_P6, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_I2C, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P7, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_I2C, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P8, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_UART, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P9, 0, 0, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_UART, 0, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P10, 0, 0, 0, {0, 0, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P11, 0, 12, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_EINT, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P12, 1, 15, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_EINT, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P13, 2, 13, 0, {VM_DCL_PIN_MODE_GPIO, VM_DCL_PIN_MODE_EINT, VM_DCL_PIN_MODE_ADC, 0 , 0, 0, 0, 0, 0, 0}},
  {VM_PIN_P14, 23, 0, 0, {0, 0, VM_DCL_PIN_MODE_EINT, 0 , 0, 0, 0, 0, 0, 0}}
};
#else
static const VM_DCL_PIN_MUX pinTable[VM_DCL_PIN_TABLE_SIZE] = {
	{VM_PIN_P0, 0, 0, 0, {0, 0, 0, 0 , 0, 0, 0, 0, 0, 0}}
};
#endif

VM_DCL_STATUS vm_dcl_config_pin_mode(VMUINT pin, VM_DCL_PIN_MODE mode)
{
	VM_DCL_HANDLE gpio_handle;
	VMINT i, j;
	VM_DCL_STATUS status = VM_DCL_STATUS_FAIL;

	for(i = 0; i<VM_DCL_PIN_TABLE_SIZE; i++)
	{
		if(pinTable[i].gpio == pin)
		{
			break;
		}
	}
	if(i >=VM_DCL_PIN_TABLE_SIZE)
		return status;
	
	gpio_handle = vm_dcl_open(VM_DCL_GPIO,pin);

	for(j = 0; j<VM_DCL_PIN_MODE_MAX; j++)
	{
		if(pinTable[i].mux[j] == mode)
		{
			vm_dcl_control(gpio_handle,4+j,NULL);
			status = VM_DCL_STATUS_OK;
			break;
		}
	}
	vm_dcl_close(gpio_handle); 
	return status;
}

VMUINT vm_dcl_pin_to_pwm(VMUINT pin)
{
	VMINT i;

	for(i = 0; i<VM_DCL_PIN_TABLE_SIZE; i++)
	{
		if(pinTable[i].gpio == pin)
		{
			return pinTable[i].pwm;
		}
	}

	return 0;
}

VMUINT vm_dcl_pin_to_channel(VMUINT pin)
{
	VMINT i;

	for(i = 0; i<VM_DCL_PIN_TABLE_SIZE; i++)
	{
		if(pinTable[i].gpio == pin)
		{
			return pinTable[i].adc;
		}
	}

	return 0;
}

VMUINT vm_dcl_pin_to_eint(VMUINT pin)
{
	VMINT i;

	for(i = 0; i<VM_DCL_PIN_TABLE_SIZE; i++)
	{
		if(pinTable[i].gpio == pin)
		{
			return pinTable[i].eint;
		}
	}

	return 0;
}
