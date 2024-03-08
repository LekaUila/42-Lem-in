/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 09:46:16 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/29 13:37:38 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*lst_tempo;
	int		size;

	lst_tempo = lst;
	size = 1;
	if (!lst)
		return (0);
	while (lst_tempo->next)
	{
		lst_tempo = lst_tempo->next;
		size++;
	}
	return (size);
}
