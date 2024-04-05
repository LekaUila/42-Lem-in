/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMI_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:33:57 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/05 15:54:03 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int AMI_getNextAntsToUse(t_ant * antList, int ants_total_number)
{
	int i = 0;

	while (i < ants_total_number + 1)
	{
		if (antList[i].actual == NULL && antList[i].toGo == NULL)
			return (i);
		i++;
	}
	return (-1);
}

static t_ant *AMI_getLastStep(t_data *data)
{
	int i = 0;
	if (!data->AMIset)
		return (NULL);
	while (data->AMIset[i])
		i++;
	if (i - 1 < 0)
		return (NULL);
	return (data->AMIset[i - 1]);	
}

int AMI_getStepNumber(t_ant **AMIset)
{
	int i = 0;
	if (!AMIset)
		return (0);
	while (AMIset[i])
		i++;
	return (i);
}

int AMI_addNewStep(t_data *data)
{
	t_ant	*new_step;
	int		i = 0;
	t_ant	**newAMIset;

	if (!data->AMIset)
	{	newAMIset = ft_calloc(2, sizeof(t_ant *));
		if (!newAMIset)
			return (-1);
		new_step = ft_calloc(data->total_ants + 1, sizeof(t_ant));
		if (!new_step)
		{
			free(new_step);
			return (-1);
		}
		newAMIset[i] = new_step;
		data->AMIset = newAMIset;
		return (0);
	}
	newAMIset = ft_calloc(AMI_getStepNumber(data->AMIset) + 2, sizeof(t_ant *));
	if (!newAMIset)
		return (-1);
	new_step = ft_calloc(data->total_ants + 1, sizeof(t_ant));
	if (!new_step)
	{
		free(new_step);
		return (-1);
	}
	while (data->AMIset[i])
	{
		newAMIset[i] = data->AMIset[i];
		i++;
	}
	newAMIset[i] = new_step;
	free(data->AMIset);
	data->AMIset = newAMIset;
	return (0);
}

void AMI_setNumberOfAntsForStart(t_data *data, int number)
{
	t_ant	*lastStep = AMI_getLastStep(data);
	int	i = AMI_getNextAntsToUse(lastStep, data->total_ants);
	int	maxIte = number + i;
	
	while (i < maxIte && i < data->total_ants + 1)
	{
		lastStep[i].actual = data->start;
		i++;
	}
}

void AMI_setNumberOfAntsForEnd(t_data *data, int number)
{
	t_ant	*lastStep = AMI_getLastStep(data);
	int	i = AMI_getNextAntsToUse(lastStep, data->total_ants);
	int	maxIte = number + i;
	
	while (i < maxIte && i < data->total_ants + 1)
	{
		lastStep[i].actual = data->end;
		i++;
	}	
}

void AMI_addAntsMovement(t_data *data, t_room *actual, t_room *toGo)
{
	t_ant	*lastStep = AMI_getLastStep(data);
	int	i = AMI_getNextAntsToUse(lastStep, data->total_ants);

	lastStep[i].actual = actual;
	lastStep[i].toGo = toGo;
}