/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:15:32 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:15:32 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(char string, int fd)
{
	write(fd, &string, 1);
}

static void	ft_rec_shownumber(int nb, int fd)
{
	char	i;

	i = (nb % 10) + 48;
	if (nb / 10 != 0)
		ft_rec_shownumber(nb / 10, fd);
	ft_print(i, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd <= 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	ft_rec_shownumber(n, fd);
}
