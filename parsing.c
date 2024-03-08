/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:14:08 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/08 16:45:52 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	fatal_error(char *line, t_data *data, char *str)
{
	if(line)
		free(line);
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
	while(maybeNbr[i])
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
	return(4);
}

/*
return 1 if the line is a start command
return 2 if the line is a end command
*/
static int checkCommandLine(line)
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
	while (str[k] != ' ' || str[k] == '\0')
		k++;
	newStr = ft_calloc(k + 1 , sizeof(char));
	if (!newStr)
		return (NULL);
	while (str[i] != ' ' || str[i] == '\0')
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
	char	**newPatways;
	
	if (nextIS)
		return (-2);
	if (ft_strlen(line) < 3)
		return (-3);
	separator = ft_strchr(line, '-');
	if (separator != line && ft_isalnum(*(separator - 1))
		&& ft_isalnum(*(separator + 1)))
	{
		if (!(*pathways))
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
			if (!(*newPatways))
				return (-666);
			for (size_t i = 0; i < ft_len_strtab(*pathways); i++)
				newPatways[i] = (*pathways)[i];
			newPatways[ft_len_strtab(*pathways)] = purifyLineByGod(line);
			if (!(*pathways)[ft_len_strtab(*pathways)])
				return (-666);
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
	while(line[i] != ' ' || line[i] != '\0')
	{
		newLine[j] = line[i];
		i++;
		j++;
	}
	while (line[i] == ' ')
		i++;
	while(line[i] != ' ' || line[i] != '\0')
	{
		newLine[j] = line[i];
		i++;
		j++;
	}
	while (line[i] == ' ')
		i++;
	while(line[i] != ' ' || line[i] != '\0')
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
		i++;
	}
	if (j != 2)
		return (-4);
	title = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if(!title)
		return (-666);
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
			return (-5);
		i++;
	}
	i++;
	y = ft_atoi(&(line[i]));
	while(line[i] != ' ' || line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
			return (-5);
		i++;
	}
	if (!data->roomList)
	{
		data->roomList = ft_calloc(2, sizeof(t_room *));
		if (!data->roomList)
			return (-666);
		data->roomList[0] = ft_calloc(1, sizeof(t_room));
		if (!data->roomList[0])
			return (-666);
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
		newRoomList = ft_calloc(lotsOfRoom(data->roomList), sizeof(t_room *));
		if (!newRoomList)
			return (-666);
		i = 0;
		while (data->roomList[i] != NULL)
		{
			newRoomList[i] = data->roomList[i];
			i++;
		}
		data->roomList[i + 1] = NULL;
		data->roomList[i]->x = x;
		data->roomList[i]->y = y;
		data->roomList[i]->room = title;
		if (NextIs == 1)
			data->roomList[i]->isStart = 1;
		else if (NextIs == 2)
			data->roomList[i]->isEnd = 1;
		free(data->roomList);
		data->roomList = newRoomList;
	}
	free(line);
	return (0);
}

void	parse(t_data *data)
{
	char	*line;
	int		nextIS;
	char	***pathways;

	line = get_next_line(0);
	nextIS = 0;
	if (isAllNum(line) == -1)
		fatal_error(line, NULL, "ANTS IS NOT A NUMBER");
	else
		data->total_ants = ft_atoi(line);
	free(line);
	while (ft_strlen(line))
	{
		line = get_next_line(0);
		if (checkTypeLine(line) == 1)
			nextIS = checkCommandLine(line);
		else if (checkTypeLine(line) == 3)
			nextIS = addPathway(line, pathways, nextIS);
		else if (checkTypeLine(line) == 4)
			nextIS = addRoom(line, data, nextIS);
		if (nextIS < 0)
			launch_fatal_error(line, data, nextIS);
		free(line);
	}
}