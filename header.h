/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:19 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/08 12:38:51 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./libft/libft.h"

typedef struct s_data;
{
	int total_ants;
	t_room	*start;
	t_room	*end;
}    	t_data;


typedef struct s_room;
{
    char	*room;
    int		ants;
    boolean	start;
    boolean	end;
    struct s_room **pathway;
}    	t_room;

#endif
