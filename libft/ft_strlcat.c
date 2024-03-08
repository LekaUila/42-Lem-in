/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:13:39 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 09:35:18 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t nb)
{
	char	*dest_tempo;

	if (!dest && nb == 0)
		return (0);
	if (nb > ft_strlen(dest) && nb != 0)
	{
		src = (char *) src;
		dest_tempo = dest + ft_strlen(dest);
		nb = nb - ft_strlen(dest);
		while (*src && nb - 1)
		{
			*dest_tempo = *src;
			src++;
			dest_tempo++;
			nb--;
		}
		*dest_tempo = 0;
		return (ft_strlen(src) + ft_strlen(dest));
	}
	return (ft_strlen(src) + nb);
}
