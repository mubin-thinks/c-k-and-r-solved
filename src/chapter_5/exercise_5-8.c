#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int day, int *output_month, int *output_day);

int main() {
        printf("%d\n", day_of_year(2026, 3, 28));
        printf("%d\n", day_of_year(2024, 7, 29));
        printf("%d\n", day_of_year(1998, 12, 31));
        printf("%d\n", day_of_year(2020, 1, 1));

        int month, day;
        month_day(2026, 87, &month, &day);
        printf("%4d/%2d/%2d\n", 2026, month, day);

        month_day(2024, 211, &month, &day);
        printf("%4d/%2d/%2d\n", 2024, month, day);

        month_day(1998, 365, &month, &day);
        printf("%4d/%2d/%2d\n", 1998, month, day);

        month_day(2020, 1, &month, &day);
        printf("%4d/%2d/%2d\n", 2020, month, day);
        return 0;
}

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
        int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
        if (
                (month < 1 || month > 12) ||
                (day < 1 || day > daytab[leap][month]) ||
                year <= 0
        ) return -1;
        for (int i = 1; i < month; i++) day += daytab[leap][i];
        return day;
}

void month_day(int year, int day, int *output_month, int *output_day) {
        int leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
        if ((day < 1 || (leap && day > 366) || (!leap && day > 365)) || year <= 0) {
                printf("error: invalid input day.\n");
                return;
        }
        int i = 1;
        for (; day > daytab[leap][i]; i++) day -= daytab[leap][i];
        *output_month = i;
        *output_day = day;
}
