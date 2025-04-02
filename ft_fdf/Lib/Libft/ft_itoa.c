/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:44:52 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 09:44:52 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_size(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		return (11);
	}
	if (n < 0 || n == 0)
	{
		n *= -1;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	fill_str(char *str, int nb, int len, int is_negati)
{
	int	i;

	i = 0;
	while (i + is_negati < len)
	{
		str[len - i - 1] = '0' + nb % 10;
		nb = (nb - nb % 10) / 10;
		i++;
	}
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		len;
	int		is_negati;

	if (nb == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	len = int_size(nb);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	is_negati = 0;
	if (nb < 0)
	{
		is_negati = 1;
		nb = -nb;
		str[0] = '-';
	}
	fill_str(str, nb, len, is_negati);
	str[len] = 0;
	return (str);
}
