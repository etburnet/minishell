/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eburnet <eburnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:23:18 by eburnet           #+#    #+#             */
/*   Updated: 2023/11/21 11:04:16 by eburnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_p(va_list ap)
{
	unsigned long int	adress;
	int					i;

	adress = va_arg(ap, unsigned long int);
	if (adress == 0)
		i = ft_putstr("(nil)");
	else
	{
		i = ft_putstr("0x");
		i += ft_putnbr_base(adress, "0123456789abcdef");
	}
	return (i);
}

int	ft_type_management(const char *format, va_list ap)
{
	int	len;

	len = 0;
	format++;
	if (*format == 'c')
		len += ft_putchar(va_arg(ap, int));
	else if (*format == 's')
		len += ft_putstr(va_arg(ap, char *));
	else if (*format == 'd' || *format == 'i')
		len += ft_putnbr(va_arg(ap, int));
	else if (*format == 'x')
		len += ft_putnbr_base(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (*format == 'X')
		len += ft_putnbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (*format == '%')
		len += ft_putchar('%');
	else if (*format == 'p')
		len += ft_p(ap);
	else if (*format == 'u')
		len += ft_putnbr_unsigned(va_arg(ap, unsigned int));
	else
		return (0);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start (ap, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			len += ft_type_management(format, ap);
			format += 2;
		}
		else
		{
			ft_putchar(*format);
			format++;
			len++;
		}
	}
	va_end(ap);
	return (len);
}

/* int	main(void)
{
	printf("%d\n", ft_printf(" %p ", (void *)12345));
	printf("%d\n\n", printf(" %p ", (void *)12345));
	printf("%d\n", ft_printf(" %X ", 255));
	printf("%d\n\n", printf(" %X ", 255));
	printf("%d\n", ft_printf(" %x ", 255));
	printf("%d\n\n", printf(" %x ", 255));
	printf("%d\n", ft_printf(" %x ", 9));
	printf("%d\n\n", printf(" %x ", 9));
	printf("%d\n", ft_printf(" %x ", 10));
	printf("%d\n\n", printf(" %x ", 10));
	printf("%d\n", ft_printf(" %x ", 11));
	printf("%d\n\n\n", printf(" %x ", 11));
	printf("%d\n", ft_printf(" %x ", -10));
	printf("%d\n\n", printf(" %x ", -10));
	printf("%d\n", ft_printf(" %x ", -11));
	printf("%d\n\n", printf(" %x ", -11));
} */