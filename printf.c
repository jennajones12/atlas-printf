#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "main.h"

/* Writes a character to stdout */
int _putchar(char c)
{
    return (write(1, &c, 1));
}

/* Prints formatted data to stdout */
int _printf(const char *format, ...)
{
    int count; /* Counter for number of characters printed */
    char c; /* Current character being processed */
    va_list args; /* Variable arguments list */
    char *str; /* Pointer to a string */
    int i, num, temp, digits; /* Integer variables used for formatting */
    const char null_str[] = "(null)"; /* String representation of NULL */

    count = 0; /* Initialize count to zero */
    va_start(args, format); /* Start variable arguments list */

    if (format == NULL) /* Check if format string is NULL */
        return (-1); /* Return -1 for error */

    /* Loop through each character in the format string */
    while ((c = *format++) != '\0')
    {
        unsigned int abs_num; /* Absolute value of a number */

        if (c == '%') /* Check if the character is a format specifier */
        {
            c = *format++; /* Move to the next character after '%' */

            if (c == '\0') /* Check if '%' is followed by '\0' */
                return (-1); /* Return the count */

            else if (c == 'c') /* Character specifier */
            {
                _putchar(va_arg(args, int)); /* Print the character */
                count++; /* Increment count */
            }
            else if (c == 's') /* String specifier */
            {
                str = va_arg(args, char *); /* Get the string argument */

                if (str == NULL) /* Check if the string is NULL */
                {
                    for (i = 0; null_str[i] != '\0'; i++) /* Print "(null)" */
                    {
                        _putchar(null_str[i]);
                        count++; /* Increment count */
                    }
                }
                else /* Print each character of the string */
                {
                    while (*str != '\0')
                    {
                        _putchar(*str++);
                        count++; /* Increment count */
                    }
                }
            }
            /* Handle signed decimal specifier */
            else if (c == 'd' || c == 'i')
            {
                num = va_arg(args, int); /* Get the integer argument */

                /* Handle special case for INT_MIN */
                if (num == INT_MIN)
                {
                    count += _putchar('-'); /* Print '-' */
                    abs_num = (unsigned int)INT_MIN; /* Get the absolute value */
                    temp = abs_num;
                    digits = 1;

                    /* Calculate number of digits in the absolute value */
                    while (temp /= 10)
                    {
                        digits *= 10;
                    }

                    /* Print each digit of the absolute value */
                    while (digits)
                    {
                        count += _putchar('0' + num / digits);
                        num %= digits;
                        digits /= 10;
                    }
                }
                else if (num < 0) /* Handle negative numbers */
                {
                    count += _putchar('-'); /* Print '-' */
                    num = -num; /* Convert to positive */
                }

                temp = num;
                digits = 1;

                /* Calculate number of digits */
                while (temp /= 10)
                    digits *= 10;

                /* Print each digit */
                while (digits)
                {
                    count += _putchar('0' + num / digits);
                    num %= digits;
                    digits /= 10;
                }
            }
            /* Handle unsigned decimal specifier */
            else if (c == 'u')
            {
                unsigned int unsigned_num = va_arg(args, unsigned int);
                temp = unsigned_num;
                digits = 1;

                /* Calculate number of digits */
                while (temp /= 10)
                    digits *= 10;

                /* Print each digit */
                while (digits)
                {
                    count += _putchar('0' + unsigned_num / digits);
                    unsigned_num %= digits;
                    digits /= 10;
                }
            }
            /* Handle unsigned octal specifier */
            else if (c == 'o')
            {
                unsigned int unsigned_num = va_arg(args, unsigned int);
                temp = unsigned_num;
                digits = 1;

                /* Calculate number of digits */
                while (temp /= 8)
                    digits *= 8;

                /* Print each digit */
                while (digits)
                {
                    count += _putchar('0' + unsigned_num / digits);
                    unsigned_num %= digits;
                    digits /= 8;
                }
            }
            /* Handle unsigned hexadecimal specifier (lowercase) */
            else if (c == 'x' || c == 'X')
            {
                unsigned int unsigned_num = va_arg(args, unsigned int);
                temp = unsigned_num;
                digits = 1;

                /* Calculate number of digits */
                while (temp /= 16)
                    digits *= 16;

                /* Print each digit */
                while (digits)
                {
                    int rem = unsigned_num / digits;

                    /* Print lowercase or uppercase hex digit */
                    count += _putchar(rem < 10 ? rem + '0' : (c == 'x' ? rem - 10 + 'a' : rem - 10 + 'A'));
                    unsigned_num %= digits;
                    digits /= 16;
                }
            }
            /* Handle pointer specifier */
            else if (c == 'p')
            {
                void *ptr = va_arg(args, void *);
                char *p;

                /* Check if pointer is NULL */
                if (ptr == NULL)
                {
                    /* Print "(nil)" */
                    const char *null_ptr_str = "(nil)";
                    while (*null_ptr_str != '\0')
                    {
                        count += _putchar(*null_ptr_str++);
                    }
                }
                else
                {
                    /* Convert pointer to string representation */
                    char buffer[20];
                    snprintf(buffer, sizeof(buffer), "%p", ptr);
                    p = buffer;

                    /* Print each character of the string */
                    while (*p != '\0')
                    {
                        count += _putchar(*p++);
                    }
                }
            }
            else if (c == '%') /* Handle '%' character */
            {
                _putchar('%'); /* Print '%' */
                count++; /* Increment count */
            }
            else /* Handle unknown format specifier */
            {
                _putchar('%'); /* Print '%' */
                _putchar(c); /* Print the unknown specifier */
                count += 2; /* Increment count by 2 */
            }
        }
        else /* Handle regular characters */
        {
            _putchar(c); /* Print the character */
            count++; /* Increment count */
        }
    }

    va_end(args); /* End variable arguments list */
    return count; /* Return the total count of characters printed */
}
