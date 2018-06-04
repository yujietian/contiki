/**
 * Copyright (c) 2015, Lukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 */

//#include <sys/stat.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
//#include "config.h"

extern void error_handler(void);
//int __errno;

int
_close(int file)
{

	return 0;
}

int
_fstat(int file, struct stat *st)
{

	return 0;
}

int
_isatty(int file)
{

	return 1;
}

int
_lseek(int file, int ptr, int dir)
{

	return 0;
}

int
_open(const char *name, int flags, int mode)
{

	return -1;
}

int
_read(int file, char *ptr, int len)
{

	return -1;
}

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");

caddr_t
_sbrk_r(struct _reent *r, int incr)
{
	extern char   end asm ("end"); /* Defined by the linker.  */
	static char * heap_end;
	char *        prev_heap_end;

	if (heap_end == NULL)
		heap_end = & end;

	prev_heap_end = heap_end;

	if (heap_end + incr > stack_ptr) {
		//errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

int
_write(int file, char *ptr, int len)
{
    int i = 0;

    switch(file)
    {
        case STDOUT_FILENO:
        case STDERR_FILENO:
            for(i=0; i<len; i++)
            {
                USART_SendData(USART1, (uint8_t)*(ptr+i));
                while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
            }
            break;
        default:
            errno = EBADF;
            return -1;
            break;
    }

	return len;
}

void
_exit (int status)
{
        while (1);
}

void
error_handler()
{
        while (1);
}

