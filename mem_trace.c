
/*

MIT License

Copyright (c) 2019 Biplab Sarkar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


*/
#include <malloc.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int show_full = 0;
//----------------------------------------------

extern void *__libc_malloc(size_t size);

static pthread_mutex_t malloc_mutex;
static pthread_mutexattr_t malloc_mutex_attr;
static int skip_malloc_print = 1;

void
malloc_init() {
    
    pthread_mutexattr_init(&malloc_mutex_attr);
    pthread_mutexattr_settype(&malloc_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&malloc_mutex, &malloc_mutex_attr);
}

void 
print_backtrace(void* array[], unsigned int bt_size) {
   
    fprintf(stderr,"[");
    for (int i = 0; i < bt_size; i++) {
        fprintf(stderr," %p ", array[i]);
    }
    fprintf(stderr,"]\n");
    fflush(stderr);
}

void *
malloc(size_t size) {
    void *result = __libc_malloc(size);
    pthread_mutex_lock(&malloc_mutex);
    if(!skip_malloc_print) {
        skip_malloc_print = 1;
        // do logging
        void *array[10];
        size_t bt_size;
        bt_size = backtrace(array, 10);
        fprintf(stderr,"== m (%u) ptr: %p ", (unsigned int) size, result);
        fflush(stderr);
        if (show_full) {
            backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
        } else {
            print_backtrace(array, bt_size);
        }
        skip_malloc_print = 0;
    }
    pthread_mutex_unlock(&malloc_mutex);
    return result;

}

//----------------------------------------------

extern void *__libc_realloc(void *ptr, size_t size);

static pthread_mutex_t realloc_mutex;
static pthread_mutexattr_t realloc_mutex_attr;
static int skip_realloc_print = 1;

void
realloc_init() {
    
    pthread_mutexattr_init(&realloc_mutex_attr);
    pthread_mutexattr_settype(&realloc_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&realloc_mutex, &realloc_mutex_attr);
}

void *
realloc(void *ptr, size_t size) {
    void *result = __libc_realloc(ptr, size);
    pthread_mutex_lock(&realloc_mutex);
    if(!skip_realloc_print) {
        skip_realloc_print = 1;
        // do logging
        void *array[10];
        size_t bt_size;
        bt_size = backtrace(array, 10);
        fprintf(stderr,"== r (%u) optr: %p ptr: %p ", 
            (unsigned int) size, ptr, result);
        fflush(stderr);
        if (show_full) {   
            backtrace_symbols_fd(array, bt_size, STDERR_FILENO);   
        } else {
            print_backtrace(array, bt_size);
        }
        skip_realloc_print = 0;
    }
    pthread_mutex_unlock(&realloc_mutex);
    return result;

}

//----------------------------------------------

extern void __libc_free(void *);

static pthread_mutex_t free_mutex;
static pthread_mutexattr_t free_mutex_attr;
static int skip_free_print = 1;

void
free_init() {
    
    pthread_mutexattr_init(&free_mutex_attr);
    pthread_mutexattr_settype(&free_mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&free_mutex, &free_mutex_attr);
}

void
free(void *ptr) {
    __libc_free(ptr);
    pthread_mutex_lock(&free_mutex);
    if(!skip_free_print) {
        skip_free_print = 1;
        // do logging
        void *array[10];
        size_t bt_size;
        bt_size = backtrace(array, 10);
        unsigned int mem_size = malloc_usable_size (ptr);
        fprintf(stderr,"== f (%u) ptr: %p ", mem_size, ptr);
        fflush(stderr);
        if (show_full) {
            backtrace_symbols_fd(array, bt_size, STDERR_FILENO);
        } else {
            print_backtrace(array, bt_size);
        }
        skip_free_print = 0;
    }
    pthread_mutex_unlock(&free_mutex);
}

// Initialize the locks
void
init_memory_management(){
    char * full = getenv("MTRACE_FULL");
    if (full != NULL) {
        show_full = 1;
    } else {
        show_full = 0;
    }
    malloc_init();
    realloc_init();
    free_init();
}

// call this before main()
void init_memory_management() __attribute__ ((constructor));

// Turn on the logic
void
enable_mem_trace() {
    skip_free_print = 0;
    skip_malloc_print = 0;
    skip_realloc_print = 0;
}

void
disable_mem_trace() {
    skip_free_print = 1;
    skip_malloc_print = 1;
    skip_realloc_print = 1;
}
