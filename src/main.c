#include"../inc/randcheck.h"

int main() {
    srand(time(NULL));
    t_ml_32 *malong = getrand(20000);

    printf("\nFinal result: %d\n", rand_test(malong));

    free(malong->arr);
    free(malong);
    return 0;
}
