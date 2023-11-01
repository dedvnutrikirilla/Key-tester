#include "../inc/randcheck.h"

void binary_out(unsigned long num, size_t size) {
    for (int i = size - 1; i >= 0; i--) {
        putchar((num & (1UL << i)) ? '1' : '0');
    }
    return;
}

void out32(t_ml_32 *ml32, int issplit) {
    for(int i = 0; i < ml32->len; i ++) {
        binary_out(ml32->arr[i], sizeof(unsigned long int) * 8);
        if (issplit)
            putchar('\n');
    }
}

t_ml_32 *getrand(int bitlen) {
    const int block_size = sizeof(unsigned long int) * 8;
    size_t len = (bitlen + block_size - 1) / block_size;
    t_ml_32 *malong = (t_ml_32 *)malloc(sizeof(t_ml_32));
    malong->len = len;
    malong->arr = (unsigned long int *)malloc(malong->len * sizeof(unsigned long int));
    for(int i = 0; i < malong->len; i ++) {
        malong->arr[i] = (unsigned long)
        ( ((rand() << 0) & 0x00000FFFul)
        | ((rand() << 12) & 0x00FFF000ul)
        | ((rand() << 24) & 0xFF000000ul));
    }
    return malong;
}
