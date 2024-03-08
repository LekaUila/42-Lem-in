/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:27:33 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/26 10:42:29 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_buffer(const char *str)
{
	size_t	i;

	str = (char *) str;
	i = 0;
	while (*str != 0 && i != BUFFER_SIZE - 1)
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen_buffer(s2) + 1;
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
	free(s1);
	free(s2);
	return (new_str);
}
