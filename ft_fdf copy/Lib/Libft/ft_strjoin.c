/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:20:48 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:20:48 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill(char const *s1, char const *s2, char	*str, int lens1)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[lens1++] = s2[i];
		i++;
	}
	str[lens1] = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		lens1;
	int		lens2;

	if (s1 && s2)
	{
		lens1 = ft_strlen(s1);
		lens2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * (lens1 + lens2 + 1));
		if (!str)
			return (NULL);
		fill(s1, s2, str, lens1);
		return (str);
	}
	return (NULL);
}
