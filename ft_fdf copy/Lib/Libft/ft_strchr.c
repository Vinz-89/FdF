/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:17:19 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:17:19 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*cursor;
	char	chr;

	cursor = (char *)s;
	chr = (char)c;
	while (cursor[0] != 0)
	{
		if (cursor[0] == chr)
			return (cursor);
		cursor++;
	}
	if (chr == 0)
		return (cursor);
	return (NULL);
}
