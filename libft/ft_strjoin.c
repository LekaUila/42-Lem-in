/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:06:06 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 13:30:54 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (new_str);
	while (i != ft_strlen(s1))
	{
		new_str[i] = s1[i];
		i++;
	}
	while (i != len)
	{
		new_str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
