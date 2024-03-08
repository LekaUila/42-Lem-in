/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_elt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:53:16 by lflandri          #+#    #+#             */
/*   Updated: 2022/11/03 19:53:31 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_elt(int index, t_list *list)
{
	if (index < 0)
		index = ft_lstsize(list) + index;
	if (index < 0 || index >= ft_lstsize(list))
		return (NULL);
	while (index != 0)
	{
		list = list->next;
		index--;
	}
	return (list);
}