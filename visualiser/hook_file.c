/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:37:15 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/12 23:50:24 by lflandri         ###   ########.fr       */
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
	if (keycode == 65362)
		data->cam_y-= CAMERA_SPEED;
	else if (keycode == 65364)
		data->cam_y+= CAMERA_SPEED;
	else if (keycode == 65361)
		data->cam_x-= CAMERA_SPEED;
	else if (keycode == 65363)
		data->cam_x+= CAMERA_SPEED;
	// ft_printf("camera position : [%d, %d]\n", data->cam_x, data->cam_y);
	// ft_printf("screen coordonate :[%d, %d] to [%d, %d]\n", data->cam_x - (WIDTH_W / 2), data->cam_y - (HEIGHT_W / 2) , data->cam_x + (WIDTH_W / 2), data->cam_y + (HEIGHT_W / 2));
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


	data = (t_data *) param;
	timet = clock();
	duration = (double)(timet - data->last_time);
	if (duration >= 0.1)
	{
		//TODO : drawmap
		data->last_time = clock();
	}
	draw_ants_colony(data);
	mlx_put_image_to_window(data->id_mlx, data->window, data->img, 0, 0);
	return (1);
}

int	ft_hook_window_destroy(void	*param)
{
	t_data	*data;

	data = (t_data *) param;
	exitVisu(data, 0);
	return (1);
}
