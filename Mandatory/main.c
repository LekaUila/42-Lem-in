/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:01:35 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/08 15:20:49 by lflandri         ###   ########.fr       */
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
		free(data->roomList);
		if (data->ants)
			free(data->ants);
	}
}

int	main(void)
{
	t_data data;
	data.end = NULL;
	data.roomList = NULL;
	data.start = NULL;
	data.total_ants = 0;
	data.ants = NULL;
	data.moveNB = 0;

	//ft_printf("parsing start\n");
	parse(&data);
	//printRooms(&data);
	//ft_printf("Checking path\n");
	checkPath(&data);
	//ft_printf("algo start\n");
	//printRooms(&data);
	startAlgo(&data);
	//ft_printf("affichage start\n");
	freeForAll(&data);
}
