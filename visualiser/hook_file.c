/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:37:15 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/12 20:36:51 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_key_hook(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	(void) param;
	if (keycode == 65307)
		exitVisu(data, 0);
	// if (keycode == 65362)
	// 	ft_mc_move(data, 0, -1, MCBS);
	// else if (keycode == 65364)
	// 	ft_mc_move(data, 0, 1, MCFS);
	// else if (keycode == 65361)
	// 	ft_mc_move(data, -1, 0, MCLS);
	// else if (keycode == 65363)
	// 	ft_mc_move(data, 1, 0, MCRS);
	// ft_affichemap(*data);
	// ft_printf("Status :\nCollectable in map : %i\nNumber of Move : %i\n\n",
	// 	data->collectable, data->move_count);
	return (1);
}
/*
keyboard code : 

esc          : 65307
top arrow    : 65362
bottom arrow : 65364
left arrow   : 65361
right arrow  : 65363
*/

int	ft_other_hook(void *param)
{
	t_data	*data;
	clock_t	timet;
	double	duration;
	int		i = 0;
	int		j = 0;
	t_room	*room;
	const int mult = (LEN_OBJECT + (BORDER * 2));
	const int add = (BORDER + (LEN_OBJECT / 2));

	data = (t_data *) param;
	timet = clock();
	duration = (double)(timet - data->last_time);
	if (duration >= 50000)
	{
		//TODO : drawmap
		draw_background(data);
	
		while (data->roomList && data->roomList[i] != NULL)
		{
			room = data->roomList[i];
			draw_room(data, room->x, room->y);
			j = 0;
			while (room->pathway && room->pathway[j])
   			{
        		draw_line(data, room->x * mult + add, room->y  * mult + add, room->pathway[j]->x * mult + add, room->pathway[j]->y * mult + add);
        		j++;
    		}
			i++;
		}
		//data->cam_x = 1;
		mlx_put_image_to_window(data->id_mlx, data->window, data->img, 0, 0);
		data->last_time = clock();
	}
	return (1);
}

int	ft_hook_window_destroy(void	*param)
{
	t_data	*data;

	data = (t_data *) param;
	exitVisu(data, 0);
	return (1);
}
