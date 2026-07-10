#include <stdio.h>

int fahr_to_celcius(int fahr);

int main() {
        printf("fahr   celcius\n");
        for (int fahr = 0; fahr <= 300; fahr = fahr + 20)
                printf("%4d   %7d\n", fahr, fahr_to_celcius(fahr));
        return 0;
}

int fahr_to_celcius(int fahr) {
        return ((fahr - 32) * 5) / 9;
}
