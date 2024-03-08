/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:25:10 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/28 10:56:51 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_bis;
	unsigned char	*s2_bis;

	s1_bis = (unsigned char *) s1;
	s2_bis = (unsigned char *) s2;
	if (n-- == 0)
		return (0);
	while (*s1_bis == *s2_bis && n)
	{
		s1_bis++;
		s2_bis++;
		n--;
	}
	return (*s1_bis - *s2_bis);
}
