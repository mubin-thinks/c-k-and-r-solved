#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
        printf("char max = %d\n", CHAR_MAX);
        printf("char min = %d\n", CHAR_MIN);
        printf("signed char max = %d\n", SCHAR_MAX);
        printf("signed char min = %d\n", SCHAR_MIN);
        printf("unsigned char max = %u\n", UCHAR_MAX);
        printf("unsigned char min = %u\n", 0);
        printf("short int max = %d\n", SHRT_MAX);
        printf("short int min = %d\n", SHRT_MIN);
        printf("unsigned short int max = %u\n", USHRT_MAX);
        printf("unsigned short int min = %u\n", 0);
        printf("int max = %d\n", INT_MAX);
        printf("int min = %d\n", INT_MIN);
        printf("unsigned int max = %u\n", UINT_MAX);
        printf("unsigned int min = %u\n", 0);
        printf("long int max = %ld\n", LONG_MAX);
        printf("long int min = %ld\n", LONG_MIN);
        printf("unsigned long int max = %lu\n", ULONG_MAX);
        printf("unsigned long int min = %lu\n", 0);
        printf("long long int max = %lld\n", LLONG_MAX);
        printf("long long int min = %lld\n", LLONG_MIN);
        printf("unsigned long long int max = %llu\n", ULLONG_MAX);
        printf("unsigned long long int min = %llu\n", 0);
        printf("float max = %e\n", FLT_MAX);
        printf("float min = %e\n", FLT_MIN);
        printf("double max = %e\n", DBL_MAX);
        printf("double min = %e\n", DBL_MIN);
        printf("long double max = %Le\n", LDBL_MAX);
        printf("long double min = %Le\n", LDBL_MIN);
        return 0;
}
