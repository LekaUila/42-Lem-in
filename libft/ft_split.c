/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 08:32:49 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 13:22:53 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(char *str, char charset)
{
	int	count;
	int	boo;

	boo = 0;
	count = 0;
	while (*str)
	{
		if (charset == *str)
				boo = 0;
		else
		{
			if (!boo)
			{
				boo = 1;
				count++;
			}
		}
		str++;
	}
	return (count);
}

static int	ft_strlen_bis(char *str, char charset)
{
	int	i;

	i = 1;
	while (*str && !(charset == *str))
	{
		i++;
		str++;
	}
	return (i);
}

static char	*create_new_str(char *str, char charset)
{
	char	*string_save;
	char	*string;

	string = malloc(sizeof(*str) * (ft_strlen_bis(str, charset)));
	if (!string)
		return (string);
	string_save = string;
	while (*str && !(charset == *str))
	{
		*string = *str;
		string++;
		str++;
	}
	*string = '\0';
	return (string_save);
}

char	**ft_split(char const *s, char c)
{
	char	boo;
	char	**tab;
	int		ind;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *) s;
	ind = 0;
	tab = ft_calloc(sizeof(char *), (count_str(str, c) + 1));
	if (!tab)
		return (tab);
	boo = 0;
	while (*str)
	{
		if (c == *str++)
				boo = 0;
		else
		{
			if (!boo)
				tab[ind++] = create_new_str(str - 1 + boo++, c);
		}
	}
	return (tab);
}
