#include    <stdint.h>
#include    <stdlib.h>
#include    <new>

void * operator new(size_t size, const std::nothrow_t&) throw()
{
	return malloc(size);
}

void operator delete(void * pobject, const std::nothrow_t&) throw()
{
	free(pobject);
}

void * operator new(size_t size)
{
	return operator new(size, std::nothrow);
}

void operator delete(void * pobject)
{
	operator delete(pobject, std::nothrow);
}

void * operator new[](size_t size)
{
	return operator new(size, std::nothrow);
}

void operator delete[](void * pobject)
{
	operator delete[](pobject, std::nothrow);
}

void * operator new[](size_t size, const std::nothrow_t&) throw()
{
	return operator new(size, std::nothrow);
}

void operator delete[](void * pobject, const std::nothrow_t&) throw()
{
	operator delete(pobject, std::nothrow);
}

