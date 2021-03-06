/*
 * newlib_stubs.c
 *
 *  Created on: 2 Nov 2010
 *      Author: nanoage.co.uk
 *
 * _sbrk changed by Alexey Dyachenko 2015
 * see http://sourceware.org/ for details
 */
#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include <stdio.h>
#include <stdint.h>                           /* Include standard types */

#include "usart.h"

#undef errno
extern int  errno;

/*
   environ
   A pointer to a list of environment variables and their values.
   For a minimal environment, this empty list is adequate:
 */
char       *__env[1] = { 0 };

char     **environ = __env;
int      _write( int file, char *ptr, int len );
int        _read( int file, char *ptr, int len );
int        _fstat( int file, struct stat *st );
int        _getpid( void );
int        _fork( void );

void _exit( int status )
{
  (void) status;
  _write( 1, "exit", 4 );
  while( 1 )
  {
    ;
  }
}

int _close( int file )
{
  (void) file;
  return -1;
}


/*
   execve
   Transfer control to a new process. Minimal implementation (for a system without processes):
 */
int _execve( char *name, char **argv, char **env )
{
  (void) name;
  (void) argv;
  (void) env;

  errno = ENOMEM;
  return -1;
}


/*
   fork
   Create a new process. Minimal implementation (for a system without processes):
 */
int _fork( void )
{
  errno = EAGAIN;
  return -1;
}


/*
   fstat
   Status of an open file. For consistency with other minimal implementations in these examples,
   all files are regarded as character special devices.
   The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
int _fstat( int file, struct stat *st )
{
  (void) file;

  st->st_mode = S_IFCHR;
  return 0;
}


/*
   getpid
   Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
 */
int _getpid( void )
{
  return 1;
}


/*
   isatty
   Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
int _isatty( int file )
{
  switch ( file )
  {
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
      return 1;
    default:

      errno = EBADF;
      return 0;
  }
}


/*
   kill
   Send a signal. Minimal implementation:
 */
int _kill( int pid, int sig )
{
  (void) pid;
  (void) sig;
  errno = EINVAL;
  return ( -1 );
}


/*
   link
   Establish a new name for an existing file. Minimal implementation:
 */
int _link( char *old, char *new )
{
  (void) old;
  (void) new;

  errno = EMLINK;
  return -1;
}


/*
   lseek
   Set position in a file. Minimal implementation:
 */
int _lseek( int file, int ptr, int dir )
{
  (void) file;
  (void) ptr;
  (void) dir;

  return 0;
}

extern unsigned int _heap;                           // Defined by the linker
extern unsigned int _eheap;                          // Defined by the linker
static caddr_t heap = NULL;

/*
   sbrk
   Increase program data space.
   Malloc and related functions depend on this
 */
caddr_t _sbrk(int incr)
{
	caddr_t prevHeap;
	caddr_t nextHeap;

	if (heap == NULL)
	{ // first allocation
		heap = (caddr_t) & _heap;
	}

	prevHeap = heap;

	// Always return data aligned on a 8 byte boundary
	nextHeap = (caddr_t) (((unsigned int) (heap + incr) + 7) & ~7);

	// Check enough space and there is no collision with stack coming the other way
	// if stack is above start of heap
	if (nextHeap >= (caddr_t) & _eheap)
	{
		errno = ENOMEM; // error - no more memory
    return ( caddr_t ) - 1;
	}
	else
	{
		heap = nextHeap;
		return (caddr_t) prevHeap;
	}
}


/*
   read
   Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
   Returns -1 on error or blocks until the number of characters have been read.
 */
int _read( int file, char *ptr, int len )
{
  int        n;
  int        num = 0;
  switch ( file )
  {
    case STDIN_FILENO:
      for( n = 0; n < len; n++ )
      {
        *ptr++ = (char) usart_getchar();
        num++;
      }
      break;

    default:
      errno = EBADF;
      return -1;
  }
  return num;
}


/*
   stat
   Status of a file (by name). Minimal implementation:
   int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */
int _stat( const char *filepath, struct stat *st )
{
  (void) filepath;
  st->st_mode = S_IFCHR;
  return 0;
}


/*
   times
   Timing information for current process. Minimal implementation:
 */
clock_t _times( struct tms * buf )
{
  (void) buf;
  return -1;
}


/*
   unlink
   Remove a file's directory entry. Minimal implementation:
 */
int _unlink( char *name )
{
  (void) name;

  errno = ENOENT;
  return -1;
}


/*
   wait
   Wait for a child process. Minimal implementation:
 */
int _wait( int *status )
{
  (void) status;
  errno = ECHILD;
  return -1;
}


/*
   write
   Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
   Returns -1 on error or number of bytes sent
 */
int _write( int file, char *ptr, int len )
{
  int        n;
  switch ( file )
  {
    case STDOUT_FILENO:                           /*stdout */
      for( n = 0; n < len; n++ )
      {
        usart_putchar( *ptr++ );
      }
      break;

    case STDERR_FILENO:                           /* stderr */
      for( n = 0; n < len; n++ )
      {
        usart_putchar( *ptr++ );
      }
      break;

    default:
      errno = EBADF;
      return -1;
  }
  return len;
}


