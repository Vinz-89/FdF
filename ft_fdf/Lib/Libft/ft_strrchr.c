/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:35:30 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:35:30 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*cursor;
	char	chr;
	int		len;

	cursor = (char *)s;
	chr = (char) c;
	len = (int)ft_strlen(s) - 1;
	if (chr == 0)
		return (cursor + len + 1);
	while (len >= 0)
	{
		if (cursor[len] == chr)
			return (cursor + len);
		len--;
	}
	return (NULL);
}
