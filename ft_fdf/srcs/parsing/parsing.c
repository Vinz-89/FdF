/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:57:31 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/14 16:57:31 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "../../Lib/Libft/libft.h"

static void	free_line_split_fd(char *line, char **list_str, int fd)
{
	get_next_line(-1);
	free(line);
	free_split(list_str);
	close(fd);
}

static char	**parse_line(char *line, t_fdf *map, int y, int fd)
{
	char	**values;

	values = ft_split(line, ' ');
	if (!values)
	{
		ft_putstr_fd("Error parsing line", 2);
		free_line_split_fd(line, values, fd);
		error_cl_exit(map);
	}
	map->map_data[y] = malloc(sizeof(int) * map->map_x);
	if (!map->map_data[y])
	{
		ft_putstr_fd("Error allocating memory for map_data[y]", 2);
		free_line_split_fd(line, values, fd);
		error_cl_exit(map);
	}
	return (values);
}

void	process_values(t_fdf *map, int y, char *line, int fd)
{
	int		x;
	long	num;
	char	**values;

	values = parse_line(line, map, y, fd);
	x = 0;
	while (x < map->map_x)
	{
		num = ft_atoi(values[x]);
		if (num < INT_MIN || num > INT_MAX)
		{
			ft_putstr_fd("value not in int format\n", 2);
			free_line_split_fd(line, values, fd);
			free(map->map_data[y]);
			map->map_data[y] = NULL;
			error_cl_exit(map);
		}
		map->map_data[y][x] = (int)num;
		if (map->map_data[y][x] < map->map_min_z)
			map->map_min_z = map->map_data[y][x];
		if (map->map_data[y][x] > map->map_max_z)
			map->map_max_z = map->map_data[y][x];
		x++;
	}
	free_split(values);
}
