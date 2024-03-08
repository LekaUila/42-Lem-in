/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:27:48 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/28 19:20:37 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	char	*dest_tempo;

	src = (char *) src;
	dest = malloc(sizeof(*src) * (ft_strlen(src) + 1));
	if (!dest)
		return (dest);
	dest_tempo = dest;
	while (*src != 0)
	{
		*dest_tempo = *src;
		src++;
		dest_tempo++;
	}
	*dest_tempo = 0;
	return (dest);
}
