/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:04:31 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 13:17:02 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_ifinstr(char c, char const *str)
{
	int		i;
	char	bool;

	i = 0;
	bool = 0;
	while (str[i])
	{
		if (str[i] == c)
			bool = 1;
		i++;
	}
	return (bool);
}

static size_t	ft_strlen_spe(char const *str, char const *set)
{
	size_t	ind;
	size_t	count;
	size_t	len;

	len = 0;
	ind = 0;
	count = 0;
	while (ft_ifinstr(str[ind], set))
		ind++;
	while (str[ind])
	{
		if (ft_ifinstr(str[ind], set))
			count++;
		else
			count = 0;
		len++;
		ind++;
	}
	len = len - count;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	int		ind;

	if (!s1 || !set)
		return (NULL);
	ind = 0;
	len = ft_strlen_spe(s1, set);
	str = (char *) ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (str);
	while (s1[ind] && ft_ifinstr(s1[ind], set))
		ind++;
	while (s1[ind] && len)
	{
		str[len - 1] = s1[ind + len - 1];
		len--;
	}
	return (str);
}
