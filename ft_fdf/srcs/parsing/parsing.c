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
#include "../../Lib/get_next_line/get_next_line.h"
#include "../../Lib/Libft/libft.h"

// Function to free allocated memory in case of an error
void	free_map_data(t_fdf *map)
{
	int	i;

	if (!map->map_data)
		return ;
	i = 0;
	while (i < map->map_y)
	{
		free(map->map_data[i]);
		i++;
	}

	free(map->map_data);
	map->map_data = NULL;
}

void	error_cl_exit(t_fdf *map)
{
	free_map_data(map);
	if (map->coord)
		free(map->coord);
	free(map);
	exit(EXIT_FAILURE);
}


void	allocate_map_data(t_fdf *map)
{
	map->map_data = malloc(sizeof(int *) * map->map_y);
	if (!map->map_data)
	{
		perror("Error allocating memory for map_data");
		exit(EXIT_FAILURE);
	}
}

// Function to count the number of columns (map_x) in the first line
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

void	handle_file_error(int fd, t_fdf *map)
{
	if (fd < 0)
	{
		perror("Error opening file");
		close(fd);
		error_cl_exit(map);
	}
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
			free(line);
			get_next_line(-1);
			close(fd);
			error_cl_exit(map);
		}
		map->map_y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}

	free(split);
}

char	**parse_line(char *line, t_fdf *map, int y)
{
	char	**values;

	values = ft_split(line, ' ');
	if (!values)
	{
		perror("Error parsing line");
		free(line);
		error_cl_exit(map);
	}

	map->map_data[y] = malloc(sizeof(int) * map->map_x);
	if (!map->map_data[y])
	{
		perror("Error allocating memory for map_data[y]");
		free_split(values);
		error_cl_exit(map);
	}

	return (values);
}

void	process_values(t_fdf *map, int y, char *line, int fd)
{
	int		x;
	long	num;
	char	**values;

	values = parse_line(line, map, y);
	x = 0;
	while (x < map->map_x)
	{
		num = ft_atoi(values[x]);
		if (num < INT_MIN || num > INT_MAX)
		{
			ft_putstr_fd("value not in int format\n", 2);
			free(line);
			free(values);
			get_next_line(-1);
			close(fd);
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

void map_parsing(t_fdf *map, char *filename)
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
