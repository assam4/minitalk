#include "ft_printf.h"

static int	print_number(int number, int fd)
{
	char	*str_num;
	int		count;

	str_num = ft_itoa(number);
	count = print_string(str_num, fd);
	free(str_num);
	return (count);
}

static int	ft_switch(char key, va_list args, int fd)
{
	if (key == 'c')
		ft_putchar_fd(va_arg(args, int), fd);
	else if (key == 's')
		return (print_string(va_arg(args, char *), fd));
	else if (key == 'p')
		return (print_ptr(va_arg(args, void *), fd));
	else if (key == 'd' || key == 'i')
		return (print_number(va_arg(args, int), fd));
	else if (key == 'u')
		return (print_unsigned(va_arg(args, unsigned int), fd));
	else if (key == 'x')
		return (print_convert_number(va_arg(args, unsigned int),
				"0123456789abcdef", fd));
	else if (key == 'X')
		return (print_convert_number(va_arg(args, unsigned int),
				"0123456789ABCDEF", fd));
	else
		ft_putchar_fd(key, fd);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		size;
	int		fd;

	if (!format || !*format)
		return (0);
	fd = 1;
	va_start(args, format);
	size = 0;
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			size += ft_switch(*format, args, fd);
		}
		else
		{
			++size;
			ft_putchar_fd(*format, fd);
		}
		++format;
	}
	va_end(args);
	return (size);
}
