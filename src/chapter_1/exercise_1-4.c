#include <stdio.h>

int main() {
        int lower, upper, step;
        float fahr, cel;

        lower = 0;
        upper = 300;
        step = 20;
        cel = lower;

        printf("celcius   fahren.\n");
        while (cel <= upper) {
                fahr = ((9.0 / 5.0) * cel) + 32.0;
                printf("%7.0f   %7.1f\n", cel, fahr);
                cel = cel + step;
        }
}
