#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include "main.h"

/**
 * _printf - Prints formatted data to stdout
 * @format: A pointer to a string containing the format specifier
 * @...: Additional arguments to be formatted according to the format specifier
 *
 * Return: The number of characters printed (excluding the null byte used to end output)
 *         or -1 if an error occurred
 */

/**
 * _putchar - Writes a character to stdout
 * @c: The character to write
 *
 * Return: On success, 1. On error, -1 is returned
 */

int _putchar(char c)
{
    return (write(1, &c, 1));
}

int _printf(const char *format, ...)
{
	int count; /* Variable to keep track of output length */
	char c; /* Alias for Format, makes it convenient to refer also format can stay in original form */
	va_list args;/* Variable to keep track of output length */
	char *str; /* String pointer to manage when c = 's' */
	int i, num, temp, digits; /* Variables to manage int printing when c = 'd' or 'i' */
	const char null_str[]; "(null)";/* Tried this variable to resolve use case of '%' differe length issue */
	unsigned int abs_num;  /* Used to resolve the INT_MIN issue using unsigned int type casting */ 

	count = 0; /* Initialize count and start variable arguments */
	va_start(args, format);

	if (format == NULL) /* Check if the format string is NULL, tried to resolve differe length issue */
		return (-1);

	 while ((c = *format++) != '\0') /* Loop through the format string until reach end of line */
	 {
		 unsigned int abs_num;
		 if (c == '%') /* Check for format specifier '%' */
		 {
			 c = *format++; /*increment c by one position to start printing characters in the string proceeding "%" */
			 if (c == '\0') /* return current count of end of line */
				 return (count);
			 else if (c == 'c')  /* check if c = 'c', and print (using _putchar) the character */
			 {
				 _putchar(va_arg(args, int));
				 count++;
			 }
			 else if (c == 's') /* Check if c= 's' */
			 {
				 str = va_arg(args, char *);
				 if (str == NULL)  /* Print "(null)" if the string is NULL, tried this for differ length issue */
				 {
					 for (i = 0; null_str[i] != '\0'; i++)
					 {
						 _putchar(null_str[i]);  
						 count++;
					 }
				 }
				 else
				 {
					 while (*str != '\0') /* traverse over the string and print each character */
					 {
						 _putchar(*str++);
						 count++;
					 }
				 }
			 }
			 else if (c == 'd' || c == 'i')  /* Handle integer specifiers 'd' and 'i', this section of code is for questions 1 d and i */
			 {
				 num = va_arg(args, int);
				 if (num == INT_MIN) /* Handle INT_MIN separately */
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
				 else if (num < 0) /* if number is negative, print a '-' character and then make the rest of the number positive by mulitiplying with -, rest will remain same as positive numbers*/
				 {
					 count += _putchar('-'); /* Handle negative numbers */
					 num = -num;
				 }
				 temp = num;
				 digits = 1;
				 while (temp /= 10)
					 digits *= 10;
				 while (digits) /* remove each digit from a number using division and modula operations, by quotient and remiander rule */
				 {
					 count += _putchar('0' + num / digits);
					 num %= digits;
					 digits /= 10;
				 }
			 }
			 else if (c == 'u')
			 {
				 unsigned int unsigned_num = va_arg(args, unsigned int);
				 temp = unsigned_num;
				 digits = 1;
				 while (temp /= 10)
					 digits *= 10;
				 while (digits)
				 {
					 count += _putchar('0' + unsigned_num / digits);
					 unsigned_num %= digits;
					 digits /= 10;
				 }
			 }
			 else if (c == 'o')
			 {
				 unsigned int unsigned_num = va_arg(args, unsigned int);
				 temp = unsigned_num;
				 digits = 1;
				 while (temp /= 8)
					 digits *= 8;
				 while (digits)
				 {
					 count += _putchar('0' + unsigned_num / digits);
					 unsigned_num %= digits;
					 digits /= 8;
				 }
			 }
			 else if (c == 'x' || c == 'X')
			 {
				 unsigned int unsigned_num = va_arg(args, unsigned int);
				 temp = unsigned_num;
				 digits = 1;
				 while (temp /= 16)
					 digits *= 16;
				 while (digits)
				 {
					 int rem = unsigned_num / digits;
					 count += _putchar(rem < 10 ? rem + '0' : (c == 'x' ? rem - 10 + 'a' : rem - 10 + 'A'));
					 unsigned_num %= digits;
					 digits /= 16;
				 }
			 }
			 else if (c == 'p')
			 {
				 void *ptr = va_arg(args, void *);
				 char *p;
				 if (ptr == NULL)
				 {
					 const char *null_ptr_str = "(nil)";
					 while (*null_ptr_str != '\0')
					 {
						 count += _putchar(*null_ptr_str++);
					 }
				 }
				 else
				 {
					 char buffer[20];
					 snprintf(buffer, sizeof(buffer), "%p", ptr);
					 p = buffer;
					 while (*p != '\0')
					 {
						 count += _putchar(*p++);
					 }
				 }
			 }
			 else if (c == '%') /* Handle '%' specifier */
			 {
				 _putchar('%');
				 count++;
			 }
			 else /* Handle unknown specifier, print '%' */
			 {
				 _putchar('%');
				 _putchar(c);
				 count += 2; /* increment by 2 because this will be a '%%' case */
			 }
		 }
		 else /*  Print non-format characters */
		 {
			 _putchar(c);
			 count++;
		 }
	 }
	 va_end(args); /* End variable arguments */
	 return count;
}
