#include "main.h"
/**
  * print_char - Prints  char
  * @types: List of arguments
  * @buffer: Buffer array -> handles print
  * @flags:  Calculates current active flags
  * @width: Width
  * @precision: The Precision specification
  * @size: Size specifier
  * Return: No of chars printed
  */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char a = va_arg(types, int);

	return (handle_write_char(a, buffer, flags, width, precision, size));
}
/* PRINT STRING */
/**
  * print_string - Prints a string
  * @types: List of arguments
  * @buffer: Buffer array to handle print
  * @flags:  Calculates active flags
  * @width: width.
  * @precision: Precisiion specification
  * @size: Sze specifier
  * Return: No of printed chars
  */
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int leng = 0;
	int i;
	char *str = va_arg(types, char *);


	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[leng] != '\0')
		leng++;
	if (precision >= 0 && precision < leng)
		leng = precision;
	if (width > leng)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], leng);
			for (i = width - leng; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - leng; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], leng);
			return (width);
		}
	}
	return (write(1, str, leng));
}
/* PRINT % SIGN */
/**
  * print_percent - Prints % sign
  * @types: List of argumnts
  * @buffer: Buffer array -> handls print
  * @flags:  Calcs curent active flags
  * @width: gets width.
  * @precision: Specification
  * @size: Siz Specifier
  * Return: No of chars printed
  */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/* PRINT INT */
/**
  * print_int - Prints int
  * @types: List of args
  * @buffer: Buffer arr -> handles print
  * @flags:  Calcs curent active flags
  * @width: gets width.
  * @precision: Precis... specification
  * @size: Siz specifier
  * Return: No of chars printed
  */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_neg = 0;
	long int m = va_arg(types, long int);
	unsigned long int num;

	m = convert_size_number(n, size);

	if (m == 0)
		buffer[j--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)m;
	if (m < 0)
	{
		num = (unsigned long int)((-1) * m);
		is_neg = 1;
	}
	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}
	j++;
	return (write_number(is_neg, j, buffer, flags, width, precision, size));
}
/* PRINT BINARY */
/**
  * print_binary - Prints an unsigned no
  * @types: List of args
  * @buffer: Buffer arr handls print
  * @flags:  Calcs curent active flags
  * @width: gets width.
  * @precision: Precisioon Specifications
  * @size: Size (Specifiier
  * Return: No of char printed.
  */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int m, n, j, total;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	m = va_arg(types, unsigned int);
	n = 2147483648; /* (2 ^ 31) */
	a[0] = m / n;
	for (j = 1; j < 32; j++)
	{
		n /= 2;
		a[j] = (m / n) % 2;
	}
	for (j = 0, total = 0, count = 0; j < 32; j++)
	{
		total += a[j];
		if (total || j == 31)
		{
			char z = '0' + a[j];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
