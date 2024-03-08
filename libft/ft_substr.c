/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:39:37 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 13:24:36 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	i = 0;
	s = (char *) s;
	start = (size_t) start;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(sizeof(char), 1));
	if (ft_strlen(s) - start >= len)
		new_str = (char *) malloc(sizeof(char) * (len + 1));
	else
		new_str = (char *) malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	if (!(new_str))
		return (new_str);
	while (i != len && s[start + i])
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
