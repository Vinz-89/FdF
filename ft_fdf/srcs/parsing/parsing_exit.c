/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:29:43 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 15:29:45 by vmeessen         ###   ########.fr       */
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
