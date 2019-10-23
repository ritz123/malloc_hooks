/* Prototypes for __malloc_hook, __free_hook */
#include <malloc.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* Prototypes for our hooks.  */

void
my_puts(char *str, size_t size) {
    for (int i = 0; i < size && str[i] != '\0'; i++)
        putc(str[i], stderr);
}

//----------------------------------------------

extern void *__libc_malloc(size_t size);

void *
malloc(size_t size) {
    void *caller = __builtin_return_address(0);
    void *result = __libc_malloc(size);

    do {
        // do logging
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "==> malloc (%u) returns %p caller: %p\n",
                (unsigned int) size, result, caller);
        my_puts(buf, sizeof(buf));

        void *array[10];
        size_t bt_size;
        //    bt_size = backtrace(array, 10);
        //    backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
    } while (0);

    return result;

}


extern void *__libc_realloc(void *ptr, size_t size);

void *
realloc(void *ptr, size_t size) {
    void *caller = __builtin_return_address(0);
    void *result = __libc_realloc(ptr, size);
    do {
        // do logging
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "==> realloc (%u | %p) returns %p caller: %p\n",
                (unsigned int) size, ptr, result, caller);
        my_puts(buf, sizeof(buf));
        void *array[10];
        size_t bt_size;
//    bt_size = backtrace(array, 10);
//    backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
    } while (0);

    return result;

}


extern void __libc_free(void *);

void
free(void *ptr) {
    void *caller = __builtin_return_address(0);
    __libc_free(ptr);
    do {
        // do logging
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "<== freed pointer %p caller: %p\n", ptr, caller);
        my_puts(buf, sizeof(buf));
        void *array[10];
        size_t bt_size;
//    bt_size = backtrace(array, 10);
//    backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
    } while (0);

}


