#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
/**
 * _printf - produce output according to format
 * @format: char string
 * Return: number of characters printed (excluding the null byte used to end output to strings)
 * check_for_specifiers - checks if there is a valid format specifier
 * @format: possible format specifier
 */
int _printf(const char *format, ...)
{
	int (*pfnc)(va_list, flags_t *);
	const char *p;
	va_list argument;
	flags_t flags = {0, 0, 0};

	register int count = 0;

	va_start(argument, format);
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == '%')
			{
				count += _putchar('%');
				continue;
			}
			while (get_flag(*p, &flags))
				p++;
			pfunc = get_print(*p);
			count += (pfnc)
				? pfnc(argument, &flags)
				: _printf("%%%c", *p);
		} else
			count += _putchar(*p);
	}
	_putchar(-1);
	va_end(argument);
	return (count);
}
