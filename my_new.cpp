
#include "my_mtrace.h"

extern "C"{
void *
malloc(int size);
void
free(void *ptr);
}

void * operator new(decltype(sizeof(0)) n) noexcept(false)
{
  	//...
	return malloc(n);
}

void * operator new[](decltype(sizeof(0)) n) noexcept(false)
{
  	//...
	return malloc(n);
}

void operator delete(void * p) noexcept(false)
{
  	//...
  	free((long unsigned int*)p);
}