#include <stdio.h>

int main() {
        int lower = 0, upper = 300, step = 20;
        float fahr = lower, cel;

        printf("fahr.   celcius\n");
        while (fahr <= upper) {
                cel = (5.0 / 9.0) * (fahr - 32.0);
                printf("%5.0f   %7.1f\n", fahr, cel);
                fahr = fahr + step;
        }
}
