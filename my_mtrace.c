/* Prototypes for __malloc_hook, __free_hook */
#include <malloc.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>



/* Prototypes for our hooks.  */

void
my_puts(char *str, size_t size) {
    for (int i = 0; i < size && str[i] != '\0'; i++)
        putc(str[i], stderr);
}

//----------------------------------------------

extern void *__libc_malloc(size_t size);

static pthread_mutex_t malloc_mutex;
static pthread_mutexattr_t malloc_mutex_attr;
static int skip_malloc_print = 0;

void
malloc_init() {
    pthread_mutexattr_init(&malloc_mutex_attr);
    pthread_mutexattr_settype(&malloc_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&malloc_mutex, &malloc_mutex_attr);
}

void *
malloc(size_t size) {
    void *caller = __builtin_return_address(0);
    void *result = __libc_malloc(size);
    pthread_mutex_lock(&malloc_mutex);
    if(!skip_malloc_print) {
        skip_malloc_print = 1;
        // do logging
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "==> malloc (%u) returns %p caller: %p\n",
                (unsigned int) size, result, caller);
        my_puts(buf, sizeof(buf));

        void *array[10];
        size_t bt_size;
        bt_size = backtrace(array, 10);
        backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
        skip_malloc_print = 0;
    }
    pthread_mutex_unlock(&malloc_mutex);
    return result;

}

//----------------------------------------------

extern void *__libc_realloc(void *ptr, size_t size);

static pthread_mutex_t realloc_mutex;
static pthread_mutexattr_t realloc_mutex_attr;
static int skip_realloc_print = 0;

void
realloc_init() {
    pthread_mutexattr_init(&realloc_mutex_attr);
    pthread_mutexattr_settype(&realloc_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&realloc_mutex, &realloc_mutex_attr);
}

void *
realloc(void *ptr, size_t size) {
    void *caller = __builtin_return_address(0);
    void *result = __libc_realloc(ptr, size);
    pthread_mutex_lock(&realloc_mutex);
    if(!skip_realloc_print) {
        skip_realloc_print = 1;
        // do logging
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "==> realloc (%u | %p) returns %p caller: %p\n",
                (unsigned int) size, ptr, result, caller);
        my_puts(buf, sizeof(buf));
        void *array[10];
        size_t bt_size;
        bt_size = backtrace(array, 10);
        backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
        skip_realloc_print = 0;
    }

    return result;

}

//----------------------------------------------

extern void __libc_free(void *);

static pthread_mutex_t free_mutex;
static pthread_mutexattr_t free_mutex_attr;
static int skip_free_print = 0;

void
free_init() {
    pthread_mutexattr_init(&free_mutex_attr);
    pthread_mutexattr_settype(&free_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&free_mutex, &free_mutex_attr);
}

void
free(void *ptr) {
    void *caller = __builtin_return_address(0);
    __libc_free(ptr);
    pthread_mutex_lock(&free_mutex);
    if(!skip_free_print) {
        skip_free_print = 1;
        // do logging
        char buf[1024] = {0};
        snprintf(buf, sizeof(buf), "<== freed pointer %p caller: %p\n", ptr, caller);
        my_puts(buf, sizeof(buf));
        void *array[10];
        size_t bt_size;
        bt_size = backtrace(array, 10);
        backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
        skip_free_print = 0;
    }
}

void
mtrace() {
    malloc_init();
    realloc_init();
    free_init();
}


