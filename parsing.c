/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:14:08 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/11 16:34:09 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void freePathways(char **pathways)
{
	if (pathways)
	{
		for (size_t i = 0; pathways[i]; i++)
		{
			free(pathways[i]);
		}	
	}
	free(pathways);
}

void    printRoom(t_room *room)
{
    int j = 0;
    ft_printf("room Name : %s\n", room->room);
    ft_printf("x : %d\n", room->x);
    ft_printf("y : %d\n", room->y);
    ft_printf("nomber of ants in room is : %d\n", room->ants);
    if (room->isStart == 1)
        ft_printf("%s is the starting room\n", room->room);
    else if (room->isEnd == 1)
        ft_printf("%s is the finishing room\n", room->room);
    while (room->pathway && room->pathway[j])
    {
        ft_printf("%s is link to room : %s\n", room->room, room->pathway[j]->room);
        j++;
    }
}

void    printRooms(t_data *data)
{
    int i = 0;

	ft_printf("\n-------------------------------------------------------------\n");
    while (data->roomList[i] != NULL)
    {
		printRoom(data->roomList[i]);
        i++;
        ft_printf("\n-------------------------------------------------------------\n\n");
    }
}


void	fatal_error(char *line, t_data *data, char *str)
{
	if(line)
		free(line);
	freeForAll(data);
	ft_putendl_fd("ERROR", 2);
	ft_error(str);
}

void launch_fatal_error(char *line, t_data *data, int error)
{
	switch (error)
	{
	case -1:
		fatal_error(line, data, "UNKNOW COMMAND");
		break;
	case -2:
		fatal_error(line, data, "COMMAND CANNOT AFFECT PATHWAY");
		break;
	case -3:
		fatal_error(line, data, "UNAVAILABLE PATHWAY");
		break;
	case -4:
		fatal_error(line, data, "NOT ENOUGHT ARGUMENT FOR ROOM");
		break;
	case -5:
		fatal_error(line, data, "ROOM COORDONATE IS NOT A NUMBER");
		break;
	case -6:
		fatal_error(line, data, "PATHWAYS LEAD TO A UNKNOW ROOM");
		break;
	case -7:
		fatal_error(line, data, "ROOM COORDONATE IS WRONG");
		break;
	case -8:
		fatal_error(line, data, "WRONG NUMBER OF START");
		break;
	case -9:
		fatal_error(line, data, "WRONG NUMBER OF END");
		break;
	case -10:
		fatal_error(line, data, "NO DATA");
		break;
	case -11:
		fatal_error(line, data, "ANTS NUMBER CAN BE LESS THAN 1");
		break;
	case -666:
		fatal_error(line, data, "MALLOC ERROR");
		break;
	
	default:
		fatal_error(line, data, "UNKNOW ERROR");
		break;
	}
}

int		isAllNum(char *maybeNbr)
{
	int	i;

	i = 0;
	if (!maybeNbr)
		return (-1);
	if (maybeNbr[0] == '-')
		i++;
	while(maybeNbr[i] && maybeNbr[i] != '\n')
	{
		if (!ft_isdigit(maybeNbr[i]))
			return (-1);
		i++;
	}
	return (0);

}

/*
return 1 if the line is a command
return 2 if the line is a commentaire
return 3 if the line is pathway
return 4 if the line is a room
*/
static int checkTypeLine(char *line)
{
	if (line[0] == '#')
	{
		if (line[1] == '#')
			return (1);
		return (2);
	}
	if (ft_strchr(line, '-'))
		return (3);
	if (line[0] == '\n')
		return (5);
	if (ft_strlen(line) == 0)
		return (5);
	return(4);
}

/*
return 1 if the line is a start command
return 2 if the line is a end command
*/
static int checkCommandLine(char *line)
{
	if (!ft_strncmp("##start", line, ft_strlen("##start")))
		return (1);
	else if (!ft_strncmp("##end", line, ft_strlen("##end")))
		return (2);
	return (-1);
}

char *purifyLineByGod(char *str)
{
	int i = 0;
	int j = 0;
	int k = 0;
	char	*newStr;

	if (!str)
		return (NULL);
	while (str[i] == ' ')
		i++;
	k = i;
	while (str[k] != ' ' && str[k] != '\0')
		k++;
	newStr = ft_calloc(k + 1 , sizeof(char));
	if (!newStr)
		return (NULL);
	while (str[i] != ' ' && str[i] != '\0')
	{
		newStr[j] = str[i];
		i++;
		j++;
	}
	newStr[j] = '\0';
	return (newStr);
}

int addPathway(char *line, char ***pathways, int nextIS)
{
	char	*separator;
	char	**newPatways = NULL;
	if (nextIS)
		return (-2);
	if (ft_strlen(line) < 3)
		return (-3);
	separator = ft_strchr(line, '-');
	if (separator != line && ft_isalnum(*(separator - 1))
		&& ft_isalnum(*(separator + 1)))
	{
		if (!pathways || !(*pathways))
		{
			*pathways = ft_calloc(2,  sizeof(char *));
			if (!(*pathways))
				return (-666);
			(*pathways)[0] = purifyLineByGod(line);
			(*pathways)[1] = NULL;
			if (!(*pathways)[0])	
				return (-666);
		}
		else
		{
			newPatways = ft_calloc(ft_len_strtab(*pathways) + 2, sizeof(char *));
			if (!newPatways)
				return (-666);
			for (int i = 0; i < ft_len_strtab(*pathways); i++)
			{
				newPatways[i] = (*pathways)[i];
			}
			newPatways[ft_len_strtab(*pathways)] = purifyLineByGod(line);
			if (!newPatways[ft_len_strtab(*pathways)])
			{	
				free(newPatways);
				return (-666);
			}
			newPatways[ft_len_strtab(*pathways) + 1] = NULL;
			free(*pathways);
			*pathways = newPatways;
		}
		return (0);
	}
	return (-3);
	
}

char	*purifyLineByDevil(char *line)
{
	int i = 0;
	int	j = 0;
	char	*newLine;

	if (!line)
		return (NULL);
	newLine = ft_calloc((ft_strlen(line) + 1), sizeof(char));
	if (!newLine)
		return (NULL);
	while (line[i] == ' ')
		i++;
	while(line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
	{
		newLine[j] = line[i];
		i++;
		j++;
	}
	newLine[j] = ' ';
	j++;
	while (line[i] == ' ')
		i++;
	while(line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
	{
		newLine[j] = line[i];
		i++;
		j++;
	}
	newLine[j] = ' ';
	j++;
	while (line[i] == ' ')
		i++;
	while(line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
	{
		newLine[j] = line[i];
		i++;
		j++;
	}
	return (newLine);
}

int lotsOfRoom(t_room **list)
{
	int i = 1;
	while (list[i] != NULL)
		i++;
	return (i);
}

int		addRoom(char *line, t_data *data, int NextIs)
{
	int i = 0;
	int j = 0;
	line = purifyLineByDevil(line);
	char *title;
	int x;
	int y;

	while (line[i])
	{
		if (line[i] == ' ')
			j++;
		if (line[i] == ' ' && !ft_isdigit(line[i + 1]))
		{
			free(line);
			return (-7);
		}
		i++;
	}
	if (j != 2)
	{
		free(line);
		return (-4);
	}
	title = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if(!title)
	{
		free(line);
		return (-666);
	}
	i = 0;
	while(line[i] != ' ')
	{
		title[i] = line[i];
		i++;
	}
	i++;
	x = ft_atoi(&(line[i]));
	while(line[i] != ' ')
	{
		if (ft_isdigit(line[i]) == 0)
		{
			free(title);
			free(line);
			return (-5);
		}
		i++;
	}
	i++;
	y = ft_atoi(&(line[i]));
	while(line[i] != ' ' && line[i] != '\n' && line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
		{
			free(title);
			free(line);
			return (-5);
		}
		i++;
	}
	if (!data->roomList)
	{
		data->roomList = ft_calloc(2, sizeof(t_room *));
		if (!data->roomList)
		{
			free(title);
			free(line);
			return (-666);
		}
		data->roomList[0] = ft_calloc(1, sizeof(t_room));
		if (!data->roomList[0])
		{
			free(title);
			free(line);
			return (-666);
		}
		data->roomList[1] = NULL;
		data->roomList[0]->x = x;
		data->roomList[0]->y = y;
		data->roomList[0]->room = title;
		if (NextIs == 1)
			data->roomList[0]->isStart = 1;
		else if (NextIs == 2)
			data->roomList[0]->isEnd = 1;
	}
	else
	{
		t_room **newRoomList;
		newRoomList = ft_calloc(lotsOfRoom(data->roomList) + 2, sizeof(t_room *));
		if (!newRoomList)
		{
			free(title);
			free(line);
			return (-666);
		}
		i = 0;
		while (data->roomList[i] != NULL)
		{
			newRoomList[i] = data->roomList[i];
			i++;
		}
		newRoomList[i + 1] = NULL;
		newRoomList[i] = ft_calloc(1, sizeof(t_room));
		if (!newRoomList[i])
		{
			free(title);
			free(line);
			free(newRoomList);
			return (-666);
		}
		newRoomList[i]->x = x;
		newRoomList[i]->y = y;
		newRoomList[i]->room = title;
		if (NextIs == 1)
			newRoomList[i]->isStart = 1;
		else if (NextIs == 2)
			newRoomList[i]->isEnd = 1;
		free(data->roomList);
		data->roomList = newRoomList;
	}
	free(line);
	return (0);
}

char *isInPatways(char *nameRoom, char *pathway)
{
	char *sepPos = ft_strchr(pathway, '-');
	char *backend = ft_strchr(pathway, '\n');
	if (backend)
		*backend = 0;

	if (!sepPos)
		return (NULL); 
	*sepPos = 0;
	//ft_printf("room name : %s\n",nameRoom );
	//ft_printf("possiblity : room %s and room %s\n", pathway, sepPos + 1);
	if (ft_strncmp(nameRoom, sepPos + 1, ft_strlen(sepPos + 1) + 1) && ft_strncmp(nameRoom, pathway, ft_strlen(pathway) + 1))
	{
		*sepPos = '-';
		//ft_printf("not good name\n");
		return (NULL);
	}
	if (!ft_strncmp(nameRoom, sepPos + 1, ft_strlen(sepPos + 1) + 1))
		return (pathway);
	if (!ft_strncmp(nameRoom, pathway, ft_strlen(pathway) + 1))
		return (sepPos + 1);
	return (NULL);
}

t_room *findRoom(char *name, t_room **roomList)
{
	int i = 0;
	if (roomList == NULL)
		return (NULL);
	while (roomList[i])
	{
		if (!ft_strncmp(name, roomList[i]->room, ft_strlen(roomList[i]->room) + 1))
			return (roomList[i]);
		i++;	
	}
	return(NULL);
}

int addRoomToRoomPathways(t_room *actual, t_room *toAdd)
{
	int i = 0;
	//printRoom(actual);
	//printRoom(toAdd);
	if (!actual->pathway)
	{
		actual->pathway = ft_calloc(2, sizeof(t_room *));
		if (!actual->pathway)
			return (-666);
		actual->pathway[1] = NULL;
		actual->pathway[0] = toAdd;
	}
	else
	{
		t_room **newRoomList;
		newRoomList = ft_calloc(lotsOfRoom(actual->pathway) + 2, sizeof(t_room *));
		if (!newRoomList)
			return (-666);
		i = 0;
		while (actual->pathway[i] != NULL)
		{
			newRoomList[i] = actual->pathway[i];
			i++;
		}
		newRoomList[i + 1] = NULL;
		newRoomList[i] = toAdd;
		free(actual->pathway);
		actual->pathway = newRoomList;
	}
	return (0);
}

void addPathToRoom(t_data *data, char **pathways)
{
	int i = 0;
	int j = 0;
	char *roomTolink = NULL;
	t_room *newroom = NULL;

	while(data->roomList[i] != NULL)
	{
		j = 0;
		while(pathways[j])
		{
			roomTolink = NULL;
			roomTolink = isInPatways(data->roomList[i]->room, pathways[j]);
			if (roomTolink && !findRoom(roomTolink, data->roomList[i]->pathway))
			{	
				//ft_printf("room %s want to link to room %s \n",data->roomList[i]->room , roomTolink);
				newroom = findRoom(roomTolink, data->roomList);
				if (!newroom)
				{
					freePathways(pathways);
					launch_fatal_error(NULL, data, -6);
				}
				if (addRoomToRoomPathways(data->roomList[i], newroom))
				{
					freePathways(pathways);
					launch_fatal_error(NULL, data, -666);
				}
				if (addRoomToRoomPathways(newroom, data->roomList[i]))
				{
					freePathways(pathways);
					launch_fatal_error(NULL, data, -666);
				}					
			}
			j++;
		}
		i++;
	}

}

void	checkStartEnd(t_data *data)
{
	int	cptStart = 0;
	int cptEnd = 0;
	int i = 0;
	t_room	*start;
	t_room	*end;
	while(data->roomList[i] != NULL)
	{
		if (data->roomList[i]->isStart == 1)
		{
			cptStart++;
			start = data->roomList[i];
		}
		else if (data->roomList[i]->isEnd == 1)
		{
			cptEnd++;
			end = data->roomList[i];
		}
		i++;
	}
	if (cptStart != 1)
		launch_fatal_error(NULL, data, -8);
	if (cptEnd != 1)
		launch_fatal_error(NULL, data, -9);
	data->start = start;
	data->end = end;
}

void	parse(t_data *data)
{
	char	*line;
	int		nextIS;
	char	**pathways = NULL;

	line = get_next_line(0);
	nextIS = 0;
	if (isAllNum(line) == -1)
		fatal_error(line, NULL, "ANTS IS NOT A NUMBER");
	else
	{
		if (ft_atoi(line) < 1)
			launch_fatal_error(line, data, -11);
		data->total_ants = ft_atoi(line);
	}
	while (ft_strlen(line))
	{
		free(line);
		line = get_next_line(0);
		if (!line)
			break;
		if (checkTypeLine(line) == 1)
			nextIS = checkCommandLine(line);
		else if (checkTypeLine(line) == 3)
			nextIS = addPathway(line, &pathways, nextIS);
		else if (checkTypeLine(line) == 4)
			nextIS = addRoom(line, data, nextIS);
		else if (checkTypeLine(line) == 5)
			break;
		if (nextIS < 0)
		{
			freePathways(pathways);
			launch_fatal_error(line, data, nextIS);
		}
	}
	free(line);
	addPathToRoom(data, pathways);
	freePathways(pathways);
	checkStartEnd(data);
}