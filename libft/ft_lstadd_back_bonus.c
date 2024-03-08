/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:20:38 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/04 16:22:21 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_tempo;

	if (!lst)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		lst_tempo = ft_lstlast(*lst);
		lst_tempo->next = new;
	}
}
