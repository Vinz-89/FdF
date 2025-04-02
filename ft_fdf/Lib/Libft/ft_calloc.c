/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:42:20 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 09:42:20 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
-> calloc

List of an type

*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;
	size_t			i;

	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}
