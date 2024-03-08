/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:55:54 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/27 12:59:52 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*s1_bis;
	char	*s2_bis;

	s1_bis = (char *) s1;
	s2_bis = (char *) s2;
	if (n-- == 0)
		return (0);
	while (*s1_bis == *s2_bis && *s1_bis && n)
	{
		s1_bis++;
		s2_bis++;
		n--;
	}
	return (*(unsigned char *)s1_bis - *(unsigned char *)s2_bis);
}
