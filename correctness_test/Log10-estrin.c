#define __RLIBM_FAST_ELEM__ rlibm_log10_estrin
#include "LibTestHelper.h"


int main(int argc, char** argv) {

    if (argc != 2) {
        printf("UsageL %s <oracle file>\n", argv[0]);
        exit(0);
    }
    
    RunTest(argv[1]);
    return 0;
}
