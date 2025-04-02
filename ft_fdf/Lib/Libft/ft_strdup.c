/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:20:11 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:20:11 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*copy;

	size = ft_strlen(s);
	copy = malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < size)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}
