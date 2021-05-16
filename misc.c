#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "defs.h"

int GetTimeMs() { 
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec*1000 + t.tv_usec/1000;
}