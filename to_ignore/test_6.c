#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void got_alarm(int sig) {
    fprintf(stderr, "Got signal %d\n", sig);
}

int main() {
    alarm(5*60);
    signal(SIGALRM, got_alarm);
    int c = getchar();
    printf("getchar returned %x\n", c);
    return 0;
}