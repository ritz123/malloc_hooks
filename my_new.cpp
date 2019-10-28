
#include "my_mtrace.h"

#include <cctype>
using namespace std;

extern "C"{

void *malloc(long unsigned size);
void free(void *ptr);

}


void* operator new(std::size_t n) noexcept(false){
	return malloc(n);
} 

void  operator delete(void* p) noexcept(false) {
	free(p);
}

void* operator new[](std::size_t n) noexcept(false) {
	return malloc(n);
} 

void  operator delete[](void* p) noexcept(false) {
	free(p);
}