/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:01:35 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/11 15:55:31 by lflandri         ###   ########.fr       */
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
	free(data->roomList);
}

int	main(void)
{
	t_data data;
	data.end = NULL;
	data.roomList = NULL;
	data.start = NULL;
	data.total_ants = 0;
	parse(&data);
	printRooms(&data);
	


	freeForAll(&data);
	exit(0);
}
