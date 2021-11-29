#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define MAX_POINTS 299997
#define MAX_COORD 2000000000

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int num;
    if (argc == 1) {
        num = rand() % MAX_POINTS + 3;
    } else {
        num = atoi(argv[1]);
    }
     
    printf("1\n%d\n", num);
    for (int i = 0; i < num; i++) {
        int a = rand() % MAX_COORD - MAX_COORD / 2;
        int b = rand() % MAX_COORD - MAX_COORD / 2;
        printf("%d %d\n", a, b);
    }
}