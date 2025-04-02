/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:36:25 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:36:25 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i;
	int		y;
	char	*result;

	i = 0;
	while (s1[i] != 0 && ft_isset(s1[i], set))
	{
		i++;
	}
	if (s1[i] == 0)
	{
		result = (char *)malloc(sizeof(char) * 1);
		if (!result)
			return (NULL);
		result[0] = 0;
		return (result);
	}
	y = ft_strlen(s1);
	while (ft_isset(s1[y - 1], set))
	{
		y--;
	}
	result = ft_substr(s1, i, y - i);
	return (result);
}
