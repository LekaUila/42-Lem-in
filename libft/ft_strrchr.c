/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:46:52 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/27 15:52:38 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*src;
	char	*save;

	src = (char *) s;
	if (c == 0)
		return (src + (ft_strlen(src)));
	save = NULL;
	while (*src != 0)
	{
		if (*src == (char) c)
			save = src;
		src++;
	}
	return (save);
}
