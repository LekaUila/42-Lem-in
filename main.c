/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:01:35 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/04 16:18:22 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	freeForAll(t_data *data)
{
	int	i = 0;

	if (data)
	{
		while (data->roomList && data->roomList[i] != NULL)
		{
			free(data->roomList[i]->room);
			free(data->roomList[i]->pathway);
			free(data->roomList[i]);
			i++;
		}
		i = 0;
		if (data->AMIset)
		{
			while (data->AMIset[i])
			{
				free(data->AMIset[i]);
				i++;
			}
			free(data->AMIset);
		}
		free(data->roomList);
		if (data->ants)
			free(data->ants);
	}
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
	clock_t	timet1;
    clock_t	timet2;

	timet1 = clock();
	data.end = NULL;
	data.roomList = NULL;
	data.start = NULL;
	data.total_ants = 0;
	data.cam_x = WIDTH_W / 2;
	data.cam_y = HEIGHT_W / 2;
	data.cam_speed = CAMERA_SPEED_START;
	data.isPaused = 1;
	data.isOnlyNext = 0;
	data.stepAdvancement = 0;
	data.AMIset = NULL;
	data.stepActual = 0;
	data.ants = NULL;
	data.moveNB = 0;

	ft_printf("parsing start\n");
	parse(&data);
	//ft_printf("room = %d\n", data.ants->room);
	printRooms(&data);
	ft_printf("Checking path\n");
	checkPath(&data);
	ft_printf("algo start\n");
	printRooms(&data);
	startAlgo(&data);
    timet2 = clock();
	data.calculationTime = (double)(timet2 - timet1);
	ft_printf("affichage start\n");
	//freeForAll(&data);
	//TEST
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0], data.roomList[0]->pathway[0]);
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0]->pathway[0], data.roomList[0]->pathway[0]->pathway[0]);
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0]->pathway[0]->pathway[0], data.roomList[0]->pathway[0]->pathway[0]->pathway[0]);
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0]->pathway[0]->pathway[0]->pathway[0], data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]);
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0], data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]);
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0], data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]);
	// AMI_addNewStep(&data);
	// AMI_addAntsMovement(&data, data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0], data.roomList[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]->pathway[0]);

	//ENDTEST


	data.last_time = clock();
	data.id_mlx = mlx_init();
	data.window = mlx_new_window(data.id_mlx, WIDTH_W, HEIGHT_W, "LEM-IN");
	data.img = mlx_new_image(data.id_mlx, WIDTH_W, HEIGHT_W);
	mlx_hook(data.window, 17, 0, ft_hook_window_destroy, &data);
	mlx_hook(data.window, 2, 1L, ft_key_hook, &data);
	mlx_mouse_hook(data.window, ft_mouse_hook, &data);
	mlx_loop_hook(data.id_mlx, ft_other_hook, &data);
	mlx_loop(data.id_mlx);
	
	exitVisu(&data, 0);
}
