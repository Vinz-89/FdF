/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:55:52 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 16:38:20 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	finding_backslash(char **rest, char **line, char *buffer)
{
	char	*cursor;

	cursor = ft_strchr(buffer, '\n');
	if (cursor != NULL)
	{
		cursor[0] = 0;
		*line = ft_strjoin_fs1(*line, buffer);
		if (!*line)
			return (1);
		free(*rest);
		*rest = ft_strdup(cursor + 1);
		if (!(*rest))
			return (1);
		*line = ft_strjoin_fs1(*line, "\n");
		if (!*line)
			return (1);
		return (1);
	}
	return (0);
}

static int	gen_line_from_txt(int fd, char **rest, char **line, char *buffer)
{
	int	nbr;

	nbr = 1;
	while (nbr > 0)
	{
		if (finding_backslash(rest, line, buffer))
		{
			return (1);
		}
		*line = ft_strjoin_fs1(*line, buffer);
		if (!line)
			return (0);
		nbr = read(fd, buffer, BUFFER_SIZE);
		if (nbr == 0)
			break ;
		if (nbr <= -1)
		{
			free(*line);
			*line = NULL;
			return (1);
		}
		buffer[nbr] = 0;
	}
	return (0);
}

static char	*get_the_line(int fd, char **rest, char *line, char *buffer)
{
	if (*rest == NULL)
	{
		*rest = ft_strdup("");
		if ((*rest) == NULL)
		{
			free(line);
			return (NULL);
		}
	}
	if (gen_line_from_txt(fd, rest, &line, buffer))
	{
		return (line);
	}
	if (line == NULL)
		return (NULL);
	if (line[0] != 0)
	{
		*rest[0] = 0;
		return (line);
	}
	free(line);
	return (NULL);
}

static char	*initialize_line(int fd, char **rest, char *buffer)
{
	char	*line;

	line = ft_strdup("");
	if (line == NULL)
		return (NULL);
	line = get_the_line(fd, rest, line, buffer);
	if (line && line[0] == 0)
	{
		free(line);
		free(*rest);
		*rest = NULL;
		return (NULL);
	}
	if (!line)
	{
		free(*rest);
		*rest = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (rest)
			free(rest);
		return (NULL);
	}
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	if (rest)
		ft_strlcpy(buffer, rest, ft_strlen(rest) + 1);
	line = initialize_line(fd, &rest, buffer);
	free(buffer);
	return (line);
}
