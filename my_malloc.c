/* Prototypes for __malloc_hook, __free_hook */
#include <malloc.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
/* Prototypes for our hooks.  */



//----------------------------------------------

extern void *__libc_malloc(size_t size);

int malloc_hook_active = 1;

void*
my_malloc_hook (size_t size, void *caller);
void
my_free_hook (void* ptr, void *caller);

void*
malloc (size_t size)
{
  void *caller = __builtin_return_address(0);
  if (malloc_hook_active)
    return my_malloc_hook(size, caller);
  return __libc_malloc(size);
}

void*
my_malloc_hook (size_t size, void *caller)
{
  void *result;

  // deactivate hooks for logging
  malloc_hook_active = 0;

  result = malloc(size);

  // do logging
  printf ("==> malloc (%u) returns %p\n", (unsigned int) size, result);

  void *array[10];
  size_t bt_size;
  bt_size = backtrace(array, 10);
  backtrace_symbols_fd(array, bt_size, STDERR_FILENO);

  // reactivate hooks
  malloc_hook_active = 1;

  return result;
}


extern void  __libc_free(void*);

void
free (void* ptr)
{
  if (malloc_hook_active) {
    void *caller = __builtin_return_address(0); 
    my_free_hook(ptr, caller);
  }
  else 
    __libc_free(ptr);
  
}

void
my_free_hook (void* ptr, void *caller)
{
  // deactivate hooks for logging
  malloc_hook_active = 0;

  free(ptr);

  // do logging
  printf ("<== freed pointer %p returns %p\n", ptr, caller);

  void *array[10];
  size_t bt_size;
  bt_size = backtrace(array, 10);
  backtrace_symbols_fd(array, bt_size, STDERR_FILENO);

  // reactivate hooks
  malloc_hook_active = 1;

}

