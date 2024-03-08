/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:05:55 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 09:34:44 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_bis;
	unsigned char	*src_bis;
	size_t			i;

	src_bis = (unsigned char *) src;
	dest_bis = (unsigned char *) dest;
	if (!dest && ! src)
		return (dest);
	if (src_bis < dest_bis)
	{
		while (0 != n)
		{
			--n;
		*(dest_bis + n) = *(src_bis + n);
		}
	}
	else
	{
		i = 0;
		while (i++ != n)
		*(dest_bis + i - 1) = *(src_bis + i - 1);
	}
	return (dest);
}
