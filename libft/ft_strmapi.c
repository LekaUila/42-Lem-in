/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:16:14 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 13:32:24 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	new_str = (char *) ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!new_str)
		return (new_str);
	while (s[i])
	{
		new_str[i] = (*f)(i, s[i]);
		i++;
	}
	return (new_str);
}
