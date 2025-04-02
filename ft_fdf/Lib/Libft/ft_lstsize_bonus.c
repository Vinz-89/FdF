/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:10:45 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:10:45 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*cursor;
	int		i;

	i = 0;
	cursor = lst;
	while (cursor)
	{
		cursor = cursor->next;
		i++;
	}
	return (i);
}
