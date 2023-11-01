#include"../inc/randcheck.h"

int test_1_monobit(t_ml_32 *malong) {
    const int block_size = sizeof(unsigned long int) * 8;
    unsigned long long total = 0;
    for (int i = 0; i < malong->len; i++) {
        for (int j = 0; j < block_size; j ++) {
            unsigned long bit = malong->arr[i] & (1UL << j);
            total += bit > 0 ? 1U : 0U;
        }
    }

    if (total > 9654 && total < 10346)
        return 1;
    return 0;
}

int test_2_maxsequence(t_ml_32 *malong) {
    const int block_size = sizeof(unsigned long int) * 8;
    unsigned long max1 = 0, max0 = 0, previous_bit = 0, bit;
    unsigned short count = 0;
    
    for (int i = 0; i < malong->len; i++) {
        for (int j = 0; j < block_size; j ++) {
            bit = malong->arr[i] & (1UL << j);
            if(bit > 0U && previous_bit == 0U) {
                if (max0 < count)
                    max0 = count;
                count = 1;
            }
            else if(bit == 0U && previous_bit > 0U) {
                if (max1 < count)
                    max1 = count;
                count = 1;
            }
            else {
                count++;
            }
            //printf("max0 - %lu | max1 - %lu | bit - %lu\t| prevbit - %lu\n", max0, max1, bit, previous_bit);
            previous_bit = bit;
            if (count >= 36)
                return 0;
        }
    }

    // in case u want to get the last sequence length
    // if (bit == 0U && max0 < count)
    //     max0 = count;
    // else if (bit > 0U && max1 < count)
    //     max1 = count;

    return 1;
}

int test_3_poker (t_ml_32 *malong) {
    const int block_size = sizeof(unsigned long int) * 8;

    unsigned int m_counters[16] = {0};
    // if `m = 4`, then there are only 16 possible
    // combinations of `m` block (0x0 - 0xF)
    // array iterator would represent `m` block,
    // while value in array represents its occurance

    for (int i = 0; i < malong->len; i++) {
        for (int j = 0; j < block_size; j+=4) {
            unsigned long block = ((malong->arr[i] >> j) & 0x0000000F);
            m_counters[block] += 1;
            //printf("\n %x & 0xF = %x; %d", (malong->arr[i] >> j), ((malong->arr[i] >> j) & 0x0000000F), m_counters[block]);
        }
    }

    /*for (int i = 0; i < 16; i++) {
        printf("\n%x - %d", i, m_counters[i]);
    }*/
    
    double k = (malong->len * block_size / 4); // 5000
    double sum = 0.0;
    for (int i = 0; i < 16; i++) {
        sum += m_counters[i] * m_counters[i];
    }
    double X = 16.0 / k * sum - k;
    if (X > 1.03 && X < 57.4)
        return 1;
    return 0;
}

int test_4_sequencelengths (t_ml_32 *malong) {
    const int block_size = sizeof(unsigned long int) * 8;
    unsigned long previous_bit = 0, bit;
    short count0 = 0, count1 = 0;
    int seqlengths0[6] = {0}, seqlengths1[6] = {0};
    
    for (int i = 0; i < malong->len; i++) {
        for (int j = 0; j < block_size; j ++) {
            bit = (malong->arr[i] & (1UL << j)) >> j;

            if(bit!= previous_bit) {
                if (bit == 0) {
                    if (count1 > 6) count1 = 6;
                    seqlengths1[count1 - 1] += 1;
                } else {
                    if (count0 > 6) count0 = 6;
                    seqlengths0[count0 - 1] += 1;
                }
                count0 = count1 = 0;
            } 
            
            if (bit == 0) count0++;
            else count1++;
            previous_bit = bit;
        }
    }

    if (bit == 0) {
        if (count1 > 6) count1 = 6;
        seqlengths1[count1 - 1] += 1;
    } else {
        if (count0 > 6) count0 = 6;
        seqlengths1[count0 - 1] += 1;
    }

    /*for (int i = 0; i < 6; i++) {
        printf("\n0 : %d - %d", i, seqlengths0[i]);
    }
    for (int i = 0; i < 6; i++) {
        printf("\n1 : %d - %d", i, seqlengths1[i]);
    }*/

    // check the sequence
    if (seqlengths0[0] < 2267 || seqlengths1[0] < 2267
    || seqlengths0[0] > 2733 || seqlengths1[0] > 2733

    || seqlengths0[1] < 1079 || seqlengths1[1] < 1079
    || seqlengths0[1] > 1421 || seqlengths1[1] > 1421

    || seqlengths0[2] < 502 || seqlengths1[2] < 502
    || seqlengths0[2] > 748 || seqlengths1[2] > 748

    || seqlengths0[3] < 223 || seqlengths1[3] < 223
    || seqlengths0[3] > 402 || seqlengths1[3] > 402

    || seqlengths0[4] < 90 || seqlengths1[4] < 90
    || seqlengths0[4] > 223 || seqlengths1[4] > 223

    || seqlengths0[5] < 90 || seqlengths1[5] < 90
    || seqlengths0[5] > 223 || seqlengths1[5] > 223) 
        return 0;
    return 1;
}

int rand_test(t_ml_32 *malong) {
    int t1, t2, t3, t4;
    t1 = test_1_monobit(malong);
    t2 = test_2_maxsequence(malong);
    t3 = test_3_poker(malong);
    t4 = test_4_sequencelengths(malong);

    printf("\ntest 1 monobit: %d\ntest 2 max sequence: %d\ntest 3 Poker: %d\ntest 4 sequence lengths: %d\n", t1, t2, t3, t4);

    if (t1 && t2 && t3 && t4)
        return 1;
    return 0;
}
