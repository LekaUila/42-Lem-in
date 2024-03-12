/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:19 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/12 14:36:27 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"


typedef struct s_room
{
    char				*room;
	int					x;
	int					y;
    long long int		ants;
    char				isStart;
    char				isEnd;
    struct s_room		 **pathway;
}    	t_room;

typedef struct s_data
{
	int total_ants;
	t_room	*start;
	t_room	*end;
	t_room	**roomList;
}    	t_data;

void	freeForAll(t_data *data);
void	parse(t_data *data);
void	fatal_error(char *line, t_data *data, char *str);
void    printRooms(t_data *data);

#endif
