#include <stdlib.h>
#include <stdio.h>
#include "my_mtrace.h"

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
    mtrace();
    func1();
}