/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:29:43 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 16:15:08 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Function to free allocated memory in case of an error
void	free_map_data(t_fdf *map)
{
	int	i;

	if (!map->map_data)
		return ;
	i = 0;
	while (i < map->map_y && map->map_data[i])
	{
		free(map->map_data[i]);
		i++;
	}
	free(map->map_data);
	map->map_data = NULL;
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

void	error_cl_exit(t_fdf *map)
{
	free_map_data(map);
	if (map->coord)
		free(map->coord);
	free(map);
	exit(EXIT_FAILURE);
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

void	allocate_map_data(t_fdf *map)
{
	map->map_data = malloc(sizeof(int *) * map->map_y);
	if (!map->map_data)
	{
		perror("Error allocating memory for map_data");
		exit(EXIT_FAILURE);
	}
}
