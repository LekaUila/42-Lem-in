/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:15:28 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/02 09:51:00 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_tempo;
	t_list	*new_lst;

	if (!lst || !f || !del)
		return (NULL);
	lst_tempo = ft_lstnew((*f)(lst->content));
	new_lst = lst_tempo;
	lst = lst->next;
	while (lst)
	{
		lst_tempo->next = ft_lstnew((*f)(lst->content));
		if (!(lst_tempo->next))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lst_tempo = lst_tempo->next;
		lst = lst->next;
	}
	return (new_lst);
}
