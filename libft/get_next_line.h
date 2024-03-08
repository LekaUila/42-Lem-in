/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:27:36 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/08 15:51:20 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include "libft.h"

size_t	ft_strlen_buffer(const char *str);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif