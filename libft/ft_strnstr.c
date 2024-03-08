/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:55:54 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/28 19:17:03 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*str;
	size_t	i;

	if (!big && len == 0)
		return (0);
	str = (char *) big;
	little = (char *) little;
	if (!(*little) || !(little))
		return (str);
	while (*str && len)
	{
		i = 0;
		while (str[i] && str[i] == little[i] && len - i++)
		{
			if (!(little[i]))
				return (str);
		}
		str++;
		len--;
	}
	return (0);
}
