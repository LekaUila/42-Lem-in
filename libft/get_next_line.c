/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:27:31 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/21 13:06:47 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_static_reload(char *text, char save_buff[BUFFER_SIZE])
{
	int	ind;

	ind = 0;
	while (*text != '\n' && *text)
		text++;
	if (*text == '\n')
	{
		text++;
		while (text[ind])
		{
			save_buff[ind] = text[ind];
			ind++;
		}
	}
	save_buff[ind] = 0;
}

static char	*ft_line_refining(char *text, char save_buff[BUFFER_SIZE])
{
	int		ind1;
	int		ind2;
	char	*line;

	ind1 = 0;
	ind2 = 0;
	while (text[ind1] != '\n' && text[ind1])
		ind1++;
	if (text[ind1] == '\n')
		ind1++;
	line = ft_calloc(sizeof(char), ind1 + 1);
	if (!line)
	{
		free(text);
		return (line);
	}
	while (ind2 != ind1)
	{
		line[ind2] = text[ind2];
		ind2++;
	}
	ft_static_reload(text, save_buff);
	free(text);
	return (line);
}

static char	*ft_create_line(char *text, char save_buff[BUFFER_SIZE], int fd)
{
	int		check_reader;
	char	*buffer;
	char	*txt_tempo;

	check_reader = BUFFER_SIZE;
	while (check_reader == BUFFER_SIZE && !ft_strchr(text, '\n'))
	{
		buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!buffer)
		{
			free(text);
			return (buffer);
		}
		check_reader = read(fd, buffer, BUFFER_SIZE);
		if (check_reader == -1)
		{
			free(text);
			return (buffer);
		}
		txt_tempo = ft_strjoin_gnl(text, buffer);
		text = txt_tempo;
	}
	return (ft_line_refining(text, save_buff));
}

static char	*ft_init_str(char save_buff[BUFFER_SIZE])
{
	char	*text;
	size_t	ind;

	ind = 0;
	if (save_buff[0])
	{
		text = ft_calloc(sizeof(char), ft_strlen_buffer(save_buff) + 1);
		while (ind != ft_strlen_buffer(save_buff))
		{
			text[ind] = save_buff[ind];
			ind++;
		}
		return (text);
	}
	text = ft_calloc(1, 1);
	return (text);
}

char	*get_next_line(int fd)
{
	char		*text;
	static char	save_buff[BUFFER_SIZE] = {0};

	if (!BUFFER_SIZE)
		return (0);
	text = ft_init_str(save_buff);
	if (!text)
	{
		free(text);
		save_buff[0] = 0;
		return (NULL);
	}
	text = ft_create_line(text, save_buff, fd);
	if (!text || !(*text))
	{
		free(text);
		save_buff[0] = 0;
		return (NULL);
	}
	return (text);
}
