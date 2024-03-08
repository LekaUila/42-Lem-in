/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:42:02 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 09:28:17 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_bis;
	unsigned char	*src_bis;

	if (!dest && !src)
		return (dest);
	src_bis = (unsigned char *) src;
	dest_bis = (unsigned char *) dest;
	while (0 != n)
	{
		--n;
		*(dest_bis + n) = *(src_bis + n);
	}
	return (dest);
}
