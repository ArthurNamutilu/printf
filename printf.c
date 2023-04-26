#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "main.h"
/**
  * write_and_count - writes to stdout
  * @fld: file descriptor -> 1 for the std output
  * @buf: buffer to be written to output stream
  * @n: size of buffer
  * @count: no of characters written to the output stream
  *
  * Return: count;
  */
int write_and_count(int fld, void *buf, size_t n, int count)
{
	write(fld, buf, n);
	count++;
	return (count);
}
/**
  * handle_integers - formats signed decimal integers
  * @args: aguments to be formatted
  * @char_printed_count: number of characters printed to the output stream
  *
  * Return: retuns char_printd_count
  */

int handle_integers(int char_printed_count, va_list args)
{
	char buff[32];
	int nums, lens, write_res;

	nums = va_arg(args, int);
	lens = sprintf(buff, "%d", nums);
	write_res = write(1, buff, lens);
	if (write_res < 0)
	{
		return (char_printed_count);
	}
	char_printed_count += write_res;
	return (char_printed_count);
}
/**
  * handle_strings - formats a string
  * @char_printed_count: number of characters printed to the output stream
  * @args: arguments to format
  * @type: character or string
  *
  * Return: (char_printed_count)
  */
int handle_strings(int char_printed_count, va_list args, char type)
{
	char j, *s;
	int write_res;

	if (type == 'j')
	{
		j = va_arg(args, int);
		write_res = write(1, &j, 1);
		if (write_res < 0)
			return (char_printed_count);
		char_printed_count++;
		return (char_printed_count);
	}
	else if (type == 's')
	{
		s = va_arg(args, char *);
		while (*s != '\0')
		{
			write_res = write(1, s, 1);
			if (write_res < 0)
				return (char_printed_count);
			s++;
			char_printed_count++;

		}
	}
	return (char_printed_count);
}

/**
  * _printf - prints formated text to stdout
  * @format: how the text be formatted
  * Return: no of characters printed
  */
int _printf(const char *format, ...)
{
	va_list args, int j = 0, char_printed_count = 0, char c;

	va_start(args, format);
	while (format && format[j] != '\0')
	{
		if (format[j] == '%')
		{
			j++;
			switch (format[j])
			{
				case 'd':
				case 'i':
					char_printed_count = handle_integers(char_printed_count, args);
					break;
				case 'b':
					char_printed_count = handle_binary_conversion(char_printed_count, args);
					break;
				case 'c':
					char_printed_count = handle_strings(char_printed_count, args, 'c');
					break;
				case 's':
					char_printed_count = handle_strings(char_printed_count, args, 's');
					break;
				case '%':
					char_printed_count = write_and_count(1, "%", 1, char_printed_count);
					break;
				default:
					break;
			}
		}
		else
		{
			c = format[j];
			char_printed_count = write_and_count(1, &c, 1, char_printed_count);
		}
		j++;
	}
	va_end(args);
	return (char_printed_count);
}
