
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

#include <stdlib.h>
#include <stdio.h>
#include "mem_trace.h"

void func1(void) {
    int j;
    void *ptr[2];
    for (j = 0; j < 2; j++) {
        ptr[j] = malloc(100);
    }

    for (j = 0; j < 2; j++) {
        ptr[j] = realloc(ptr[j], 300);
    }

    for (j = 0; j < 2; j++) {
        free (ptr[j]);
    }
}



int
main(int argc, char *argv[]) {
    enable_mem_trace();
    func1();
}