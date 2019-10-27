#include <stdlib.h>
#include <stdio.h>
#include "my_mtrace.h"
using  namespace std;

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



int
main(int argc, char *argv[]) {
    mtrace();
    func1();
}