#include <stdlib.h>
#include <stdio.h>

void func1(void) {
    int j;
    void *ptr[2];
    for (j = 0; j < 2; j++) {
        ptr[j] = malloc(100);
    }

    for (j = 0; j < 2; j++) {
        ptr[j] = realloc(ptr[j], 300);
    }
}

void
memory_management_init();

int
main(int argc, char *argv[]) {
    memory_management_init();
    func1();
    getchar();
    exit(EXIT_SUCCESS);
}