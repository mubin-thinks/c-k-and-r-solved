#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
        printf("char max = %d\n", CHAR_MAX);
        printf("char min = %d\n", CHAR_MIN);
        printf("signed char max = %d\n", SCHAR_MAX);
        printf("signed char min = %d\n", SCHAR_MIN);
        printf("unsigned char max = %d\n", UCHAR_MAX);
        printf("unsigned char min = %d\n", 0);
        printf("int max = %d\n", INT_MAX);
        printf("int min = %d\n", INT_MIN);
        printf("signed int max = %d\n", SHRT_MAX);
        printf("signed int min = %d\n", SHRT_MIN);
        printf("unsigned int max = %d\n", UINT_MAX);
        printf("unsigned int min = %d\n", 0);
        printf("long int max = %d\n", LONG_MAX);
        printf("long int min = %d\n", LONG_MIN);
        printf("unsigned long int max = %d\n", ULONG_MAX);
        printf("unsigned long int min = %d\n", 0);
        printf("float max = %e\n", FLT_MAX);
        printf("float min = %e\n", FLT_MIN);
        printf("double max = %e\n", DBL_MAX);
        printf("double min = %e\n", DBL_MIN);
        printf("long double max = %Le\n", LDBL_MAX);
        printf("long double min = %Le\n", LDBL_MIN);
        return 0;
}
