/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:45:23 by lflandri          #+#    #+#             */
/*   Updated: 2022/10/21 13:05:04 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *str, ...);
int		ft_write_nb(char str, va_list *parameter);
int		ft_write_hexa(char str, va_list *parameter);
int		ft_write_char(va_list *parameter);
int		ft_write_str(va_list *parameter);
int		ft_hexa(unsigned long long nb, char low);
int		ft_deci(long long int nb);
int		ft_z_case(void);
#endif