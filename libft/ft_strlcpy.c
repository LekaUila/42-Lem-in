/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:13:14 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/27 20:41:44 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	char	*dest_tempo;

	if (n != 0)
	{
		src = (char *) src;
		dest_tempo = dest;
		while (*src && n - 1)
		{
			*dest_tempo = *src;
			src++;
			dest_tempo++;
			n--;
		}
		*dest_tempo = 0;
		return (ft_strlen(src) + ft_strlen(dest));
	}
	return (ft_strlen(src) + n);
}
