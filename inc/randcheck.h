#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct s_ml_32 {
    unsigned long int *arr; // array of 32 bit int blocks
    int len; // number of blocks
} t_ml_32;

// test
int rand_test(t_ml_32 *malong); // test battery
// tests themselves. You do not normally need them here, but for testing purposes, OK
int test_1_monobit(t_ml_32 *malong);
int test_2_maxsequence(t_ml_32 *malong);
int test_3_poker (t_ml_32 *malong);
int test_4_sequencelengths (t_ml_32 *malong);
//
// utils
void out32(t_ml_32 *ml32, int issplit);
t_ml_32 *getrand(int bitlen); // pseudo randomer
//