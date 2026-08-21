#include <stdio.h>
#include <stdarg.h>
#include <limits.h>

void min_printf(char *fmt, ...);

int main() {
        int x = 20;
        min_printf(
                "some tests: %d %i %o %x %X %u %c %s %f %e %E %g %G %p %% %a %b %h %j\n",
                30,
                30,
                255,
                256,
                257,
                UINT_MAX,
                'a',
                "test",
                1.234567,
                1.234567,
                1.234567,
                1.234567,
                1.234567,
                &x
        );
        return 0;
}

void min_printf(char *fmt, ...) {
        va_list arg;
        va_start(arg, fmt);
        for (char *p = fmt; *p; p++) {
                if (*p != '%') {
                        putchar(*p);
                        continue;
                }
                switch (*(++p)) {
                case 'd': case 'i':
                        printf("%d", va_arg(arg, int));
                        break;
                case 'o':
                        printf("%o", va_arg(arg, int));
                        break;
                case 'x': case 'X':
                        printf("%x", va_arg(arg, int));
                        break;
                case 'u':
                        printf("%u", va_arg(arg, unsigned int));
                        break;
                case 'c':
                        printf("%c", va_arg(arg, int));
                        break;
                case 's':
                        for (char *s = va_arg(arg, char *); *s; s++)
                                putchar(*s);
                        break;
                case 'f':
                        printf("%f", va_arg(arg, double));
                        break;
                case 'e': case 'E':
                        printf("%e", va_arg(arg, double));
                        break;
                case 'g': case 'G':
                        printf("%g", va_arg(arg, double));
                        break;
                case 'p':
                        printf("%p", va_arg(arg, void *));
                        break;
                default:
                        putchar(*p);
                        break;
                }
        }
        va_end(arg);
}
