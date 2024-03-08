/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:08:05 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/28 19:16:19 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_bis;

	s_bis = (unsigned char *) s;
	while (0 != n--)
	{
		if (*s_bis == (unsigned char) c)
			return (s_bis);
		s_bis++;
	}
	return (NULL);
}
