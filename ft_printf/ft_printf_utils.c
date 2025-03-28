#include "ft_printf.h"

int	print_string(const char *str, int fd)
{
	if (str)
	{
		ft_putstr_fd((char *)str, fd);
		return (ft_strlen(str));
	}
	else
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
}

int	print_convert_number(unsigned int num, const char *base, int fd)
{
	size_t	base_len;
	int		count;

	base_len = ft_strlen(base);
	count = 0;
	if (num >= (unsigned int)base_len)
		count += print_convert_number(num / base_len, base, fd);
	ft_putchar_fd(base[num % base_len], fd);
	return (++count);
}

static int	print_convert_number2(unsigned long num, const char *base, int fd)
{
	size_t	base_len;
	int		count;

	base_len = ft_strlen(base);
	count = 0;
	if (num >= (unsigned int)base_len)
		count += print_convert_number2(num / base_len, base, fd);
	ft_putchar_fd(base[num % base_len], fd);
	return (++count);
}

int	print_ptr(const void *pointer, int fd)
{
	if (pointer)
		return (print_string("0x", fd)
			+ print_convert_number2((unsigned long)pointer,
				"0123456789abcdef", fd));
	else
		return (print_string("(nil)", fd));
}

int	print_unsigned(unsigned int number, int fd)
{
	int		count;
	char	letter;

	count = 0;
	if (number > 9)
		count += print_unsigned(number / 10, fd);
	letter = number % 10 + '0';
	write(fd, &letter, 1);
	return (++count);
}
