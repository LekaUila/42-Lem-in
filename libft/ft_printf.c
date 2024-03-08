/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:30:29 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/10 10:45:29 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_parameter_analysis_system(const char *str, va_list *parameter)
{
	if (*str == '%')
	{
		if (write(1, str, 1) == -1)
			return (-1);
		return (1);
	}
	else if (*str == 'u' || *str == 'd' || *str == 'i')
		return (ft_write_nb(*str, parameter));
	else if (*str == 'c')
		return (ft_write_char(parameter));
	else if (*str == 's')
		return (ft_write_str(parameter));
	else if (*str == 'x' || *str == 'X' || *str == 'p')
		return (ft_write_hexa(*str, parameter));
	else
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		write(1, str, 1);
		return (2);
	}
}

static int	ft_printfbis(const char *str, int i, int count, va_list *parameter)
{
	int	ret;

	while (str[i])
	{
		if (str[i] == '%')
		{
			ret = ft_parameter_analysis_system(str + i + 1, parameter);
			if (ret < 0)
				return (-1);
			count += ret;
			i = i + 2;
		}
		else
		{
			if (write(1, str + i, 1) == -1)
				return (-1);
		i++;
		count++;
		}
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	parameter;
	int		i;
	int		count;

	count = 0;
	i = 0;
	va_start(parameter, str);
	count = ft_printfbis(str, i, count, &parameter);
	va_end(parameter);
	return (count);
}
