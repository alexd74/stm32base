// wrappers for the non-reentrant newlib syscalls

#include <stdlib.h>
#include <stdio.h>
#include <reent.h>
#include <sys/stat.h>
#include <sys/unistd.h>

_ssize_t _read_r(
    struct _reent *r, 
    int file, 
    void *ptr, 
    size_t len)
{
	return _read(file, ptr, len);
}

_ssize_t _write_r (
    struct _reent *r, 
    int file, 
    const void *ptr, 
    size_t len)
{
	return _write(file, ptr, len);
}

int _open_r(struct _reent *r, const char *a, int b, int c)
{
  return _open(a,b,c);
}

int _close_r(
    struct _reent *r, 
    int file)
{
	return _close(file);
}

_off_t _lseek_r(
    struct _reent *r, 
    int file, 
    _off_t ptr, 
    int dir)
{
	return _lseek(file, ptr, dir);
}

int _fstat_r(
    struct _reent *r, 
    int file, 
    struct stat *st)
{
	return _fstat(file, st);
}

void * _sbrk_r(
    struct _reent *_s_r, 
    ptrdiff_t nbytes)
{
	return _sbrk(nbytes);
}
