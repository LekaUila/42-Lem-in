/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:20:17 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 09:26:12 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*made_malloc(long int n, int sign)
{
	long int	num;
	char		*tab;

	num = 0;
	while (n != 0)
	{
		num++;
		n = n / 10;
	}
	tab = (char *) ft_calloc(sizeof(char), (num + 1 + sign));
	if (!tab)
		return (tab);
	return (tab + num - 1 + sign);
}

static char	*ft_itoa_bis(long int n, int sign, char *str)
{
	if (!str)
		return (str);
	if (n == 0)
	{		
		if (sign)
		{
			*str = 45;
			return (str);
		}
		return (str + 1);
	}
	else
	{
		*str = n % 10 + 48;
		return (ft_itoa_bis(n / 10, sign, str - 1));
	}
}

char	*ft_itoa(int n)
{
	char		*tab;
	long int	nb;

	nb = n;
	if (nb < 0)
		return (ft_itoa_bis(-nb, 1, made_malloc(nb, 1)));
	else if (nb == 0)
	{
		tab = ft_calloc(sizeof(char), 2);
		if (!tab)
			return (tab);
		tab[0] = 48;
		return (tab);
	}
	else
		return (ft_itoa_bis(nb, 0, made_malloc(nb, 0)));
}
