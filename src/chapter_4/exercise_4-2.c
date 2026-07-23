#include <stdio.h>
#include <ctype.h>

double atof(const char s[]);

int main() {
        // Accuracy errors maybe present in doubles.
        printf("%f\n", atof("12.34"));
        printf("%.10f\n", atof("-1e-10"));
        printf("%f\n", atof("-1240234.234235stop32740234"));
        printf("%f\n", atof("1e50"));
        printf("%f\n", atof("3e10"));
        printf("%.10f\n", atof("3e-10"));
        printf("%f\n", atof("0e-10"));
        return 0;
}

double atof(const char s[]) {
        double val = 0.0, power = 1.0, exponent = 1.0;
        int i = 0, sign, exponent_sign,  exponent_val = 0;
        for (; isspace(s[i]); i++);
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') i++;
        for (; isdigit(s[i]); i++) val = 10.0 * val + (s[i] - '0');
        if (s[i] == '.') i++;
        for (; isdigit(s[i]); i++) {
                val = 10.0 * val + (s[i] - '0');
                power *= 10.0;
        }
        if (s[i] != 'E' && s[i] != 'e') return (sign * val) / power;
        i++;
        exponent_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') i++;
        for (; isdigit(s[i]); i++) exponent_val = 10 * exponent_val + (s[i] - '0');
        for (int i = 0; i < exponent_val; i++) exponent *= 10.0;
        if (exponent_sign < 0) exponent = 1.0 / exponent;
        return ((sign * val) / power) * exponent;
}
