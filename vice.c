#include <stdio.h>
#include <time.h>
#include "defs.h"

int main(void) {

    // Random seed initialization, should only be called once
    srand(time(NULL));

    /* intialise default setup*/
    allInit();

    return 0;
}
