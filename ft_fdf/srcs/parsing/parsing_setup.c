/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:33:08 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 16:39:30 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "../../Lib/Libft/libft.h"

int	count_columns(char *line)
{
	int	count;
	int	in_number;

	count = 0;
	in_number = 0;
	while (*line)
	{
		if (*line != ' ' && in_number == 0)
		{
			in_number = 1;
			count++;
		}
		else if (*line == ' ')
		{
			in_number = 0;
		}
		line++;
	}
	return (count);
}

static void	free_line_fd(char *line, int fd)
{
	free(line);
	close(fd);
}

/*
Determine la taille de la map avant allocation de memoire
*/
void	get_map_size(t_fdf *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_file_error(fd, map);
	map->map_y = 0;
	map->map_x = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->map_y == 0)
			map->map_x = count_columns(line);
		else if (map->map_x != count_columns(line))
		{
			ft_putstr_fd("Error in your terrain\n", 2);
			get_next_line(-1);
			free_line_fd(line, fd);
			error_cl_exit(map);
		}
		map->map_y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	filename_check(t_fdf *map, char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".fdf", 4) != 0)
	{
		ft_putstr_fd("Usage : ./fdf <filename.fdf>\n", 2);
		error_cl_exit(map);
	}
}

void	map_parsing(t_fdf *map, char *filename)
{
	int		fd;
	char	*line;
	int		y;

	filename_check(map, filename);
	fd = open(filename, O_RDONLY);
	handle_file_error(fd, map);
	get_map_size(map, filename);
	map->map_min_z = 0;
	map->map_max_z = 0;
	allocate_map_data(map);
	y = 0;
	get_next_line(-1);
	line = get_next_line(fd);
	while (line)
	{
		process_values(map, y, line, fd);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
}
