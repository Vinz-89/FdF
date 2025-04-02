/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:13:00 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:13:00 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*t_dest;
	unsigned char	*t_src;
	size_t			i;

	if (!dest && !src)
		return (dest);
	if (dest == src)
		return (dest);
	t_dest = (unsigned char *)dest;
	t_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		t_dest[i] = t_src[i];
		i++;
	}
	return (dest);
}
