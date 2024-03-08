/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:40:01 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/27 15:52:28 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*src;

	src = (char *) s;
	if (c == 0)
		return (src + (ft_strlen(src)));
	while (*src != 0)
	{
		if (*src == (char) c)
			return (src);
		src++;
	}
	return (NULL);
}
