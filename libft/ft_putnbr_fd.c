/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <lflandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:30:48 by lflandri          #+#    #+#             */
/*   Updated: 2022/09/28 16:53:16 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_bis(long int n, int fd)
{
	if (n == 0)
		return ;
	ft_putnbr_fd_bis(n / 10, fd);
	ft_putchar_fd(n % 10 + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd(45, fd);
		ft_putnbr_fd_bis(-nb, fd);
	}
	else if (nb == 0)
		ft_putchar_fd(48, fd);
	else
		ft_putnbr_fd_bis(nb, fd);
}
