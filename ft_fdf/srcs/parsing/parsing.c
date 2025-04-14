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


void	handle_file_error(int fd, t_fdf *map)
{
	if (fd < 0)
	{
		perror("Error opening file");
		free_map_data(map);
		if (!map->coord)
			free(map->coord);
		free(map);
		exit(EXIT_FAILURE);
	}
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

/*
Determine la taille de la map avant allocation de memoire
*/
void	get_map_size(t_fdf *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	map->map_y = 0;
	map->map_x = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->map_y == 0)
			map->map_x = count_columns(line);
		map->map_y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	value;
	int	sign;

	i = 0;
	value = 0;
	sign = 1;
	while (nptr[i] == ' ' || ('\t' <= nptr[i] && nptr[i] <= '\r'))
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		value = value * 10 + (nptr[i] - 48);
		i++;
	}
	return (value * sign);
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
		free_map_data(map);
		exit(EXIT_FAILURE);
	}

	map->map_data[y] = malloc(sizeof(int) * map->map_x);
	if (!map->map_data[y])
	{
		perror("Error allocating memory for map_data[y]");
		free_split(values);
		free(line);
		free_map_data(map);
		exit(EXIT_FAILURE);
	}

	return (values);
}

void	process_values(char **values, t_fdf *map, int y)
{
	int	x;

	x = 0;
	while (x < map->map_x)
	{
		map->map_data[y][x] = ft_atoi(values[x]);

		if (map->map_data[y][x] < map->map_min_z)
			map->map_min_z = map->map_data[y][x];
		if (map->map_data[y][x] > map->map_max_z)
			map->map_max_z = map->map_data[y][x];

		x++;
	}
}

void map_parsing(t_fdf *map, char *filename)
{
	int		fd;
	char	*line;
	int		y;
	char	**values;

	fd = open(filename, O_RDONLY);
	handle_file_error(fd, map);
	get_map_size(map, filename);
	map->map_min_z = 0;
	map->map_max_z = 0;
	allocate_map_data(map);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		values = parse_line(line, map, y);
		process_values(values, map, y);

		free_split(values);
		free(line);
		line = get_next_line(fd);
		y++;
	}

	close(fd);
}


// Function to parse the map file and store values in `map->map_data`
void map_parsing2(t_fdf *map, char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    get_map_size(map, filename);

    // Initialize min and max values
    map->map_min_z = 0;
    map->map_max_z = 0;

    // Allocate memory for map_data
    map->map_data = malloc(sizeof(int *) * map->map_y);
    if (!map->map_data)
    {
        perror("Error allocating memory for map_data");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *line;
    int y = 0;

    // Parse each line of the file
    while ((line = get_next_line(fd)))
    {
        // Split the line into values
        char **values = ft_split(line, ' ');
        if (!values)
        {
            perror("Error parsing line");
            free(line);
            free_map_data(map);
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Allocate memory for the current row
        map->map_data[y] = malloc(sizeof(int) * map->map_x);
        if (!map->map_data[y])
        {
            perror("Error allocating memory for map_data[y]");
            free_split(values);
            free(line);
            free_map_data(map);
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Parse each value in the row
        for (int x = 0; x < map->map_x; x++)
        {
            map->map_data[y][x] = ft_atoi(values[x]);

            // Update min and max values
            if (map->map_data[y][x] < map->map_min_z)
                map->map_min_z = map->map_data[y][x];
            if (map->map_data[y][x] > map->map_max_z)
                map->map_max_z = map->map_data[y][x];
        }

        // Free the split line and the line itself
        free_split(values);
        free(line);
        y++;
    }

    close(fd);

    for(int i = 0; i < map->map_y; i++)
    {
        for (int j = 0; j < map->map_x; j++)
            printf("%d ", map->map_data[i][j]);
        printf("\n");
    }
}
