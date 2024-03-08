/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:22:58 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/08 12:30:12 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_nb(char str, va_list *parameter)
{
	unsigned int	ui;
	long int		i;

	if (str == 'u')
	{
		ui = (unsigned int) va_arg(*parameter, unsigned int);
		if (!ui)
			return (ft_z_case());
		return (ft_deci(ui));
	}
	else
	{
		i = (int) va_arg(*parameter, int);
		if (!i)
			return (ft_z_case());
		else if (i < 0)
		{
			if (write(1, "-", 1) == -1)
				return (-1);
			return (ft_deci(i * -1) + 1);
		}
		return (ft_deci(i));
	}
}

int	ft_write_char(va_list *parameter)
{
	int	c;

	c = (int) va_arg(*parameter, int);
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_write_str(va_list *parameter)
{
	char	*c;

	c = (char *) va_arg(*parameter, char *);
	if (!c)
		return (write(1, "(null)", 6));
	return (write(1, c, ft_strlen(c)));
}

int	ft_write_hexa(char str, va_list *parameter)
{
	unsigned long long	ui;

	ui = (unsigned long) va_arg(*parameter, unsigned long);
	if (str == 'p')
	{
		if (!ui)
			return (write(1, "(nil)", 5));
		if (write(1, "0x", 2) == -1)
			return (-1);
		return (ft_hexa(ui, 1) + 2);
	}
	else
	{
		if (!(unsigned int)ui)
			return (ft_z_case());
		if (str == 'x')
			return (ft_hexa((unsigned int) ui, 1));
		return (ft_hexa((unsigned int) ui, 0));
	}
}
