/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 10:07:10 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/02 09:51:09 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_tempo;

	lst_tempo = lst;
	if (!lst)
		return (lst);
	while (lst_tempo->next)
		lst_tempo = lst_tempo->next;
	return (lst_tempo);
}
