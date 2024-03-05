#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include "main.h"

int _printf(const char *format, ...) 
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format) {
        if (*format == '%') 
	{
            format++;
            switch (*format) 
	    {
                case 'c':
                    count++;
                    va_arg(args, int);
                    break;
                case 's':
                    count += vsnprintf(NULL, 0, va_arg(args, const char *), args);
                    break;
		case 'd':
		case 'i':
		case 'u':
		case 'o':
		case 'x':
		case 'X':
		case 'p':
                    count += vsnprintf(NULL, 0, "", args);
                    break;
                case '%':
                    count++;
                    break;
                default:
                    count += 2;
                    break;
            }
        } else {
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}
