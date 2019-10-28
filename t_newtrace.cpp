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