/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antsSwitcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:38:55 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/08 15:20:31 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int listPathSize(t_room ***path)
{
    int i = 0;

    while (path[i])
        i++;
    return (i);
}

static int	SwitchingCalculator(t_room ***pathToUse, int antsNB, int *listNBAntForPath)
{
	int i = 1;
	int antNBtoassign = antsNB;

	for (int i = 0; pathToUse[i]; i++)
		listNBAntForPath[i] = pathSize(pathToUse[i]);
	while (pathToUse[1] && antNBtoassign)
	{
		if ((i != 1 && listNBAntForPath[i - 1] <= listNBAntForPath[i]) || (!pathToUse[i]))
			i = 1;
		else
		{
			listNBAntForPath[i]++;
			i++;
			antNBtoassign--;
		}
	}
    if (DEBUG_PRINT)
		ft_printf("shortest can done in %d and list can done in %d\n", listNBAntForPath[0] + antsNB, listNBAntForPath[1]);
	if (listNBAntForPath[0] + antsNB < listNBAntForPath[1] || !pathToUse[1])
		return (SHORTEST_PATH);
	for (int i = 0; pathToUse[i]; i++)
		listNBAntForPath[i] -= pathSize(pathToUse[i]);
	return (LIST_PATH);
}

static int    mooveAnts(t_trueAnt *ant, t_data *data, int *canStartToEnd)
{
    if (ant->path[ant->room]->isEnd == 1)
        return (-1);
    if (ant->path[ant->room + 1]->ants != 0 && ant->path[ant->room + 1]->isEnd != 1)
		return (-1);
    if (ant->path[ant->room] == data->start && ant->path[ant->room + 1] == data->end)
	{
		if (!(*canStartToEnd))
		{
			return (-1);
		}
		*canStartToEnd = 0;
	}
    ant->path[ant->room]->ants--;
    ant->room = ant->room + 1;
    ft_printf("L%d-%s", ant->number, ant->path[ant->room]->room);
    ant->path[ant->room]->ants++;
    return (0);
}

int	AntsSwitcher(t_data *data, t_room ***pathToUse)
{
	int	*listNBAntForPath = ft_calloc(listPathSize(pathToUse) + 1, sizeof(int));
	int antsAdded = 0;
    int space = 0;
	int ind = 0;
	int canStartToEnd = 1;

	if (SwitchingCalculator(pathToUse, data->total_ants, listNBAntForPath) == SHORTEST_PATH)
	{
		for (int i = 0; i < data->total_ants; i++)
		{
			data->ants[i].path = pathToUse[0];
			data->ants[i].room = 0;
		}
	}
	else
	{
		for (int i = 1; pathToUse[i]; i++)
		{
    		if (DEBUG_PRINT)
				ft_printf("path %d need %d ants\n", i, listNBAntForPath[i]);
			for (int j = 0; j < listNBAntForPath[i]; j++)
			{
				data->ants[antsAdded].path = pathToUse[i];
				data->ants[antsAdded].room = 0;
				antsAdded++;
			}
		}
	}
	while (data->end->ants != data->total_ants)
	{
		data->moveNB++;
		ind = 0;
        while(data->ants[ind].number != -1)
        {
			space = mooveAnts(&data->ants[ind], data, &canStartToEnd);
			if (space == 0 && data->ants[ind + 1].path != NULL)
				ft_printf(" ");
            ind++;
        }
		canStartToEnd = 1;
		ft_printf("\n");
	}
	free(listNBAntForPath);
	return (0);
}