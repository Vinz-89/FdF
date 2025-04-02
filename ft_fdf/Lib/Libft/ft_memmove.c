/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:13:28 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:13:28 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;
	size_t			i;

	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	i = 0;
	if (t_dest < t_src)
	{
		while (i < len)
		{
			t_dest[i] = t_src[i];
			i++;
		}
	}
	else if (t_dest > t_src)
	{
		while (len > 0)
		{
			len--;
			t_dest[len] = t_src[len];
		}
	}
	return (dest);
}
