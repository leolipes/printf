/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leolipes <leolipes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:59:30 by leolipes          #+#    #+#             */
/*   Updated: 2021/09/11 21:02:14 by leolipes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdarg.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i++;
	write(1, s, i);
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!c)
		return (0);
	while (s[i] && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_putnbr(int nb)
{
	unsigned int	nbr;
	int				quantchar;

	quantchar = 0;
	if (nb < 0)
	{
		quantchar += ft_putchar('-');
		nbr = (unsigned int)(nb * -1);
	}
	else
		nbr = (unsigned int)nb;
	if (nbr >= 10)
		quantchar += ft_putnbr(nbr / 10);
	quantchar += ft_putchar((char)(nbr % 10 + '0'));
	return (quantchar);
}

int	ft_hexaux(size_t nb, char *base)
{
	int		quantchar;

	quantchar = 0;
	if (nb < 0)
	{
		quantchar += ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 16)
		quantchar += ft_hexaux(nb / 16, base);
	quantchar += ft_putchar((char)(base[nb % 16]));
	return (quantchar);
}

int	ft_puthexa(unsigned int nb, char *base)
{
	return (ft_hexaux(nb, base));
}

int	ft_flag_u(unsigned int nbr)
{
	int	quantchar;

	quantchar = 0;
	if (nbr >= 10)
		quantchar += ft_putnbr(nbr / 10);
	quantchar += ft_putchar((char)(nbr % 10 + '0'));
	return (quantchar);
}

int	ft_pointer(void *ptr)
{
	int	quantchar;

	quantchar = 0;
	quantchar += write (1, "0x", 2);
	quantchar += ft_hexaux((size_t)ptr, "0123456789abcdef");
	return (quantchar);
}

int	ft_check_flags(char c, va_list args)
{
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_flag_u(va_arg(args, int)));
	if (c == '%')
		return (ft_putchar(c));
	if (c == 'x')
		return (ft_puthexa(va_arg(args, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_puthexa(va_arg(args, int), "0123456789ABCDEF"));
	if (c == 'p')
		return (ft_pointer(va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	size_t	count;
	int		quantchar;

	count = 0;
	quantchar = 0;
	va_start(args, input);
	while (input[count])
	{
		if (input[count] == '%' && ft_strchr("cspdiuxX%", input[count + 1]))
		{
			quantchar += ft_check_flags(input[++count], args);
			count++;
		}
		else
		{
			quantchar += ft_putchar(input[count]);
			count++;
		}
	}
	return (quantchar);
}
