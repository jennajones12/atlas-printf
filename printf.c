#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int _putchar(char c) {
    return write(1, &c, 1);
}

void print_number_recursive(unsigned int num, unsigned int base, int *count, int uppercase) {
    char digits[] = "0123456789abcdef";
    if (uppercase) {
        digits[10] = 'A';
        digits[11] = 'B';
        digits[12] = 'C';
        digits[13] = 'D';
        digits[14] = 'E';
        digits[15] = 'F';
    }

    if (num >= base) {
        print_number_recursive(num / base, base, count, uppercase);
    }
    *count += _putchar(digits[num % base]);
}

void print_number(unsigned int num, unsigned int base, int *count, int uppercase) {
    if (num >= base) {
        print_number_recursive(num / base, base, count, uppercase);
    }
    *count += _putchar("0123456789abcdef"[num % base]);
}

void print_pointer(void *p_addr, int *count) {
    *count += _putchar('0');
    *count += _putchar('x');
    print_number((uintptr_t)p_addr, 16, count, 0);
}

void print_string(const char *str, int *count) {
    if (str == NULL) {
        str = "(null)";
    }
    while (*str != '\0') {
        *count += _putchar(*str++);
    }
}

int _printf(const char *format, ...) {
    int count = 0;
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == '\0') {
                break;
            }
            else if (*format == 'c') {
                _putchar(va_arg(args, int));
                count++;
            }
            else if (*format == 's') {
                print_string(va_arg(args, char *), &count);
            }
            else if (*format == 'd' || *format == 'i') {
                int num = va_arg(args, int);
                if (num < 0) {
                    count += _putchar('-');
                    num = -num;
                }
                print_number((unsigned int)num, 10, &count, 0);
            }
            else if (*format == 'u') {
                unsigned int u_num = va_arg(args, unsigned int);
                print_number(u_num, 10, &count, 0);
            }
            else if (*format == 'o') {
                unsigned int o_num = va_arg(args, unsigned int);
                print_number(o_num, 8, &count, 0);
            }
            else if (*format == 'x' || *format == 'X') {
                unsigned int x_num = va_arg(args, unsigned int);
                print_number(x_num, 16, &count, *format == 'X');
            }
            else if (*format == 'p') {
                void *p_addr = va_arg(args, void *);
                print_pointer(p_addr, &count);
            }
            else if (*format == '%') {
                _putchar('%');
                count++;
            }
            else {
                _putchar('%');
                _putchar(*format);
                count += 2;
            }
        }
        else {
            _putchar(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}
