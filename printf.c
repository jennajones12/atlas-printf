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
	int i, num, temp, digits;
	const char null_str[] = "(null)";
	unsigned int abs_num;

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
				str = NULL;
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
						_putchar(*str);
						str++;
						count++;
					}
				}
			}
			else if (c == 'd' || c == 'i')
			{
				num = va_arg(args, int);
				if (num == INT_MIN)
				{
					count += _putchar('-');
					abs_num = (unsigned int)INT_MIN;
					temp = abs_num;
					digits = 1;
					while (temp /= 10)
					{
						digits *= 10;
					}
					 while (digits)
					{
						count += _putchar('0' + num / digits);
						num %= digits;
						digits /= 10;
					}
				}
				else if (num < 0)
				{
					count += _putchar('-');
					num = -num;
				}
				temp = num;
				digits = 1;
				while (temp /= 10)
					digits *= 10;
				while (digits)
				{
					count += _putchar('0' + num / digits);
					num %= digits;
					digits /= 10;
				}
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
