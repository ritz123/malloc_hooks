
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
#include "my_mtrace.h"
using  namespace std;

class A {
public:
    A(){
        printf("A:A()\n");
    }
    void hi() {
        printf("hi\n");
    }
};

void func1(void) {
    int j;
    char *ptr[2];
    for (j = 0; j < 2; j++) {
        ptr[j] = new char[100];
    }


    for (j = 0; j < 2; j++) {
        delete ptr[j];
    }
}

void func2() {
    func1();
}

int
main(int argc, char *argv[]) {
    mtrace();
    func2();
    A* a = new A();
    printf("%p\n", (void*)a);
    a->hi();
    printf("========\n");
    untrace();
    func2();
    A* b = new A();
    printf("%p\n", (void*)b);
    b->hi();
    printf("========\n");
}