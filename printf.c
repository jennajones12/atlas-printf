#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "main.h"
#include <limits.h>

/**
 * 
 * 
 *
 *
 * 
 */

#include <unistd.h>

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
void print_unsigned_int(unsigned int num, int *count) {
    unsigned int temp = num;
    int digits = 1;
    while (temp /= 10) digits *= 10;
    while (digits) {
        *count += _putchar('0' + num / digits);
        num %= digits;
        digits /= 10;
    }
}

void print_octal(unsigned int num, int *count) {
    unsigned int temp = num;
    int digits = 1;
    while (temp /= 8) digits *= 8;
    while (digits) {
        *count += _putchar('0' + num / digits);
        num %= digits;
        digits /= 8;
    }
}

void print_hexadecimal(unsigned int num, int *count, int uppercase) {
    unsigned int temp = num;
    int digits = 1;
    while (temp /= 16) digits *= 16;
    while (digits) {
        int digit = num / digits;
        *count += _putchar((digit < 10 ? '0' + digit : (uppercase ? 'A' + digit - 10 : 'a' + digit - 10)));
        num %= digits;
        digits /= 16;
    }
}

void print_pointer(void *p_addr, int *count) {
    char *msg = "Address:[0x";
    while (*msg != '\0') {
        *count += _putchar(*msg);
        msg++;
    }
    print_hexadecimal((unsigned long)p_addr, count, 0);
    *count += _putchar(']');
}

int _putchar(char c)
{
	return (write(1, &c, 1));
}

int _printf(const char *format, ...)
{
    int count;
    char c;
    va_list args;
    char *str;
    int i, num;
    const char null_str[] = "(null)";

    count = 0;
    va_start(args, format);

    if (format == NULL)
        return (-1);

    while ((c = *format++) != '\0')
    {
        if (c == '%')
        {
            c = *format++;
            if (c == '\0')
                return (count);
            else if (c == 'c')
            {
                _putchar(va_arg(args, int));
                count++;
            }
            else if (c == 's')
            {
                str = va_arg(args, char *);
                if (str == NULL)
                {
                    for (i = 0; null_str[i] != '\0'; i++)
                    {
                        _putchar(null_str[i]);
                        count++;
                    }
                }
                else
                {
                    while (*str != '\0')
                    {
                        _putchar(*str++);
                        count++;
                    }
                }
            }
            else if (c == 'd' || c == 'i')
            {
                num = va_arg(args, int);
                if (num < 0)
                {
                    count += _putchar('-');
                    num = -num;
                }
                print_unsigned_int(num, &count);
            }
            else if (c == 'u')
            {
                unsigned int u_num = va_arg(args, unsigned int);
                print_unsigned_int(u_num, &count);
            }
            else if (c == 'o')
            {
                unsigned int o_num = va_arg(args, unsigned int);
                print_octal(o_num, &count);
            }
            else if (c == 'x' || c == 'X')
            {
                unsigned int x_num = va_arg(args, unsigned int);
                print_hexadecimal(x_num, &count, c == 'X');
            }
            else if (c == 'p')
            {
                void *p_addr = va_arg(args, void *);
                print_pointer(p_addr, &count);
            }
            else if (c == '%')
            {
                _putchar('%');
                count++;
            }
            else
            {
                _putchar('%');
                _putchar(c);
                count += 2;
            }
        }
        else
        {
            _putchar(c);
            count++;
        }
    }

    va_end(args);
    return count;
}
