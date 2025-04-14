/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fs1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:21:29 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/14 18:21:29 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_fs1(char *s1, char *s2)
{
	char	*str;
	int		lens1;
	int		lens2;
	int		i;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i++])
		str[i - 1] = s1[i - 1];
	i = 0;
	while (s2[i])
	{
		str[lens1++] = s2[i];
		i++;
	}
	str[lens1] = 0;
	free(s1);
	return (str);
}
