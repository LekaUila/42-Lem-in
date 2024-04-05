/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antsSwitcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:38:55 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/05 15:55:41 by lflandri         ###   ########.fr       */
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
    AMI_addAntsMovement(data, ant->path[ant->room], ant->path[ant->room + 1]);
    ant->path[ant->room]->ants--;
    ant->room = ant->room + 1;
    ft_printf("L%d-%s", ant->number, ant->path[ant->room]->room);
    ant->path[ant->room]->ants++;
    return (0);
}

void	AntsSwitcher(t_data *data, t_room ***pathToUse)
{
	int	*listNBAntForPath = ft_calloc(listPathSize(pathToUse) + 1, sizeof(int));
	int antsAdded = 0;
    int space = 0;
	int ind = 0;
	int canStartToEnd = 1;

	// ft_printf("vérification de compatibilité des chemin : \n");
	// for (int i = 1; pathToUse[i]; i++)
	// {
	// 	for (int j = 1; pathToUse[j]; j++)
	// 	{
	// 		if (j != i)
	// 			ft_printf("%d and %d result of path : %d\n", i, j,crossPath(pathToUse[i], pathToUse[j]));
	// 	}
	// }
	// ft_printf("fin vérification de compatibilité des chemin : \n");
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
		AMI_addNewStep(data);
		data->moveNB++;
		AMI_setNumberOfAntsForEnd(data, data->end->ants);
		ind = 0;
        while(data->ants[ind].number != -1)
        {
			if (data->ants[ind].path)
			{
				space = mooveAnts(&data->ants[ind], data, &canStartToEnd);
				if (space == 0 && data->ants[ind + 1].path != NULL)
					ft_printf(" ");
			}
            ind++;
        }
		canStartToEnd = 1;
		AMI_setNumberOfAntsForStart(data, data->start->ants);
		ft_printf("\n");
	}
	free(listNBAntForPath);
}