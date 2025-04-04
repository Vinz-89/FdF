/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:16:53 by vmeessen          #+#    #+#             */
/*   Updated: 2024/11/05 10:16:53 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_tab(char const *str, char splitter)
{
	int	i;
	int	w;
	int	is_word;

	is_word = 0;
	w = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == splitter)
		{
			is_word = 0;
		}
		else if (is_word == 0)
		{
			w += 1;
			is_word = 1;
		}
		i++;
	}
	return (w);
}

static char	*word(char const *str, char splitter, int pos)
{
	char	*word;
	int		s_to_split;
	int		i;
	int		j;

	j = 0;
	while (str[pos + j] != 0)
	{
		if (str[pos + j] == splitter)
			break ;
		j++;
	}
	s_to_split = j;
	word = malloc((sizeof(char) * (s_to_split + 1)));
	if (word == 0)
		return (0);
	word[s_to_split] = 0;
	i = 0;
	while (i < s_to_split)
	{
		word[i] = str[pos + i];
		i++;
	}
	return (word);
}

static void	free_all(char	**tab, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**fill_tab(char **tab, char const *s, char c)
{
	int	i;
	int	is_word;
	int	w;

	is_word = 0;
	i = 0;
	w = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			is_word = 0;
		else if (is_word++ == 0)
		{
			tab[w] = word(s, c, i);
			if (tab[w] == 0)
			{
				free_all(tab, w);
				return (NULL);
			}
			w += 1;
		}
		i++;
	}
	tab[w] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = malloc((sizeof(char *) * (size_tab(s, c) + 1)));
	if (tab == 0)
		return (0);
	if (!fill_tab(tab, s, c))
		return (NULL);
	return (tab);
}
