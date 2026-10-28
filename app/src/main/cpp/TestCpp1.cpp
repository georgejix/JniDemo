#include "TestCpp1.h"

int testCpp1() {
    LOGD("testCpp1-testCpp1");
    int array1[5] = {1, 2, 3, 4, 5};
    //使用引用类型，可以修改数组中原数据的值
    for (int &i1: array1) {
        i1 = i1 * 2;
    }
    for (int index1 = 0; index1 < sizeof(array1) / sizeof(array1[0]); index1++) {
        LOGD("testCpp1-testCpp1 i2[%d]=%d", index1, array1[index1]);
    }
    return 0;
}