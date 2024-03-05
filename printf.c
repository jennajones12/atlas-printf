#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

int _putchar(char c) {
    return (write(1, &c, 1));
}

int _printf(const char *format, ...) {
    int count;
    char c;
    va_list args;
    char *str;
    int i, num, temp, digits;
    const char null_str[] = "(null)";

    count = 0;
    va_start(args, format);

    if (format == NULL)
        return (-1);

    while ((c = *format++) != '\0') {
        unsigned int abs_num;
        if (c == '%') {
            c = *format++;
            if (c == '\0')
                return (count);
            else if (c == 'c') {
                _putchar(va_arg(args, int));
                count++;
            } else if (c == 's') {
                str = va_arg(args, char *);
                if (str == NULL) {
                    for (i = 0; null_str[i] != '\0'; i++) {
                        _putchar(null_str[i]);
                        count++;
                    }
                } else {
                    while (*str != '\0') {
                        _putchar(*str++);
                        count++;
                    }
                }
            } else if (c == 'd' || c == 'i') {
                num = va_arg(args, int);
                if (num == INT_MIN) {
                    count += _putchar('-');
                    abs_num = (unsigned int)INT_MIN;
                    temp = abs_num;
                    digits = 1;
                    while (temp /= 10) {
                        digits *= 10;
                    }
                    while (digits) {
                        count += _putchar('0' + num / digits);
                        num %= digits;
                        digits /= 10;
                    }
                } else if (num < 0) {
                    count += _putchar('-');
                    num = -num;
                }
                temp = num;
                digits = 1;
                while (temp /= 10)
                    digits *= 10;
                while (digits) {
                    count += _putchar('0' + num / digits);
                    num %= digits;
                    digits /= 10;
                }
            } else if (c == 'u') {
                unsigned int unsigned_num = va_arg(args, unsigned int);
                temp = unsigned_num;
                digits = 1;
                while (temp /= 10)
                    digits *= 10;
                while (digits) {
                    count += _putchar('0' + unsigned_num / digits);
                    unsigned_num %= digits;
                    digits /= 10;
                }
            } else if (c == 'o') {
                unsigned int unsigned_num = va_arg(args, unsigned int);
                temp = unsigned_num;
                digits = 1;
                while (temp /= 8)
                    digits *= 8;
                while (digits) {
                    count += _putchar('0' + unsigned_num / digits);
                    unsigned_num %= digits;
                    digits /= 8;
                }
            } else if (c == 'x' || c == 'X') {
                unsigned int unsigned_num = va_arg(args, unsigned int);
                temp = unsigned_num;
                digits = 1;
                while (temp /= 16)
                    digits *= 16;
                while (digits) {
                    int rem = unsigned_num / digits;
                    count += _putchar(rem < 10 ? rem + '0' : (c == 'x' ? rem - 10 + 'a' : rem - 10 + 'A'));
                    unsigned_num %= digits;
                    digits /= 16;
                }
            } else if (c == 'p') {
                void *ptr = va_arg(args, void *);
                char *p;
                if (ptr == NULL) {
                    const char *null_ptr_str = "(nil)";
                    while (*null_ptr_str != '\0') {
                        count += _putchar(*null_ptr_str++);
                    }
                } else {
                    char buffer[20];
                    snprintf(buffer, sizeof(buffer), "%p", ptr);
                    p = buffer;
                    while (*p != '\0') {
                        count += _putchar(*p++);
                    }
                }
            } else if (c == '%') {
                _putchar('%');
                count++;
            } else {
                _putchar('%');
                _putchar(c);
                count += 2;
            }
        } else {
            _putchar(c);
            count++;
        }
    }
    va_end(args);
    return count;
}
