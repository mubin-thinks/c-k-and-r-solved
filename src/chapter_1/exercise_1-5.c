#include <stdio.h>

int main() {
        int fahr;
        printf("fahr.   celcius\n");
        for (fahr = 300; fahr >= 0; fahr = fahr - 20)
                printf("%5d   %7.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
}
