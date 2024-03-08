/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:13:08 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/04 17:29:17 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tempo;

	if (!lst || !del)
		return ;
	tempo = (*lst)->next;
	while (tempo)
	{
		tempo = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tempo;
	}
	ft_lstdelone(*lst, del);
}
