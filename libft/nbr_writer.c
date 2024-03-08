/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_writer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:33:49 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/08 12:30:38 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_z_case(void)
{
	return (write(1, "0", 1));
}

int	ft_hexa(unsigned long long nb, char low)
{
	char	unit;
	int		count;

	if (!nb)
		return (0);
	unit = nb % 16;
	count = ft_hexa(nb / 16, low) + 1;
	if (unit > 9)
		unit = unit + 55 + (low * 32);
	else
		unit = unit + 48;
	if (write(1, &unit, 1) == -1)
		return (-1);
	return (count);
}

int	ft_deci(long long int nb)
{
	char	unit;
	int		count;

	if (!nb)
		return (0);
	unit = nb % 10 + 48;
	count = ft_deci(nb / 10) + 1;
	if (write(1, &unit, 1) == -1)
		return (-1);
	return (count);
}
