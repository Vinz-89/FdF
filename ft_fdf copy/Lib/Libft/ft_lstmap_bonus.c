/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:49:35 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 09:49:35 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*f_list;
	t_list	*f_output;
	void	*content;

	if (!lst)
		return (NULL);
	f_list = NULL;
	while (lst)
	{
		if (f)
			content = f(lst->content);
		else
			content = lst->content;
		f_output = ft_lstnew(content);
		if (!f_output)
		{
			if (f)
				del(content);
			ft_lstclear(&f_list, del);
			return (NULL);
		}
		ft_lstadd_back(&f_list, f_output);
		lst = lst->next;
	}
	return (f_list);
}
