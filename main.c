/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:01:35 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/14 15:05:21 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	freeForAll(t_data *data)
{
	int	i = 0;

	while (data->roomList && data->roomList[i] != NULL)
	{
		free(data->roomList[i]->room);
		free(data->roomList[i]->pathway);
		free(data->roomList[i]);
		i++;
	}
	if (data->ants_list)
		free(data->ants_list);
	free(data->roomList);
}

void exitVisu(t_data *data, int er)
{
	mlx_destroy_image(data->id_mlx, data->img);
	mlx_destroy_window(data->id_mlx, data->window);
	mlx_destroy_display(data->id_mlx);
	free(data->id_mlx);
	if (er)
		launch_fatal_error(NULL, data, er);
	freeForAll(data);
	exit(0);
}

int	main(void)
{
	t_data data;
	data.end = NULL;
	data.roomList = NULL;
	data.start = NULL;
	data.total_ants = 0;
	data.cam_x = WIDTH_W / 2;
	data.cam_y = HEIGHT_W / 2;
	data.isPaused = 1;
	data.isOnlyNext = 0;
	data.stepAdvancement = 0;
	data.ants_list = NULL;
	parse(&data);
	printRooms(&data);
	data.ants_list = ft_calloc(data.total_ants + 1, sizeof(t_ant));
	if (!data.ants_list)
		launch_fatal_error(NULL, &data, -666);
	data.ants_list[0].actual = data.roomList[0];
	data.ants_list[0].toGo = data.roomList[0]->pathway[1];
	data.last_time = clock();
	data.id_mlx = mlx_init();
	data.window = mlx_new_window(data.id_mlx, WIDTH_W, HEIGHT_W, "Visu Hex");
	data.img = mlx_new_image(data.id_mlx, WIDTH_W, HEIGHT_W);
	mlx_hook(data.window, 17, 0, ft_hook_window_destroy, &data);
	mlx_hook(data.window, 2, 1L, ft_key_hook, &data);
	mlx_loop_hook(data.id_mlx, ft_other_hook, &data);
	mlx_loop(data.id_mlx);
	
	exitVisu(&data, 0);
}
