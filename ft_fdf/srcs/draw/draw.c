/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:55 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/14 13:18:55 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

// Fonction pour calculer les coordonnées projetées
/*
Update les coordonnee par rapport a la projection
et le position au centre de l'ecran et la translation
*/
void	calculate_projected_coords(t_fdf *map, int *x, int *y, int *z)
{
	if (map->view_type == 0)
		project_iso(x, y, z, map);
	else
		project_perspec(x, y, z, map);
	*x += (map->screen_w / 2) + map->pos_x;
	*y += (map->screen_h / 2) + map->pos_y;
}

/*
Dessine la ligne entre 2 points dans map->coord
*/
void	draw_projected_line(t_fdf *map)
{
	int		min_z;
	int		max_z;
	int		color1;
	int		color2;
	t_coord	*coord;

	coord = map->coord;
	min_z = map->map_min_z;
	max_z = map->map_max_z;
	color1 = calculate_color(coord->z1, min_z, max_z);
	color2 = calculate_color(coord->z2, min_z, max_z);
	calculate_projected_coords(map, &coord->x1, &coord->y1, &coord->z1);
	calculate_projected_coords(map, &coord->x2, &coord->y2, &coord->z2);
	draw_line(map, coord, color1, color2);
}

/*
Position des points avant projection
(le (0,0) est au centre de l object)
*/
void	setup_point_data(t_fdf *map, int x, int y, int type)
{
	if (type == 0)
	{
		map->coord->x1 = (x - map->map_x / 2) * map->scale;
		map->coord->y1 = (y - map->map_y / 2) * map->scale;
		map->coord->z1 = map->map_data[y][x] * map->scale / 1;
	}
	if (type == 1)
	{
		map->coord->x2 = ((x + 1) - map->map_x / 2) * map->scale;
		map->coord->y2 = (y - map->map_y / 2) * map->scale;
		map->coord->z2 = map->map_data[y][x + 1] * map->scale;
	}
	if (type == 2)
	{
		map->coord->x2 = (x - map->map_x / 2) * map->scale;
		map->coord->y2 = ((y + 1) - map->map_y / 2) * map->scale;
		map->coord->z2 = map->map_data[y + 1][x] * map->scale;
	}
}

/*
Draw les lignes de chaque point
	- Si x < map_x - 1, dessine une ligne horizontale
	- Si y < map_y - 1, dessine une ligne verticale
	- setup_point_data pour calculer les coordonnee avant projection
	- draw_projected_line pour dessiner la ligne entre les 2 points
*/
void	draw_map(t_fdf *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->map_y)
	{
		x = -1;
		while (++x < map->map_x)
		{
			setup_point_data(map, x, y, 0);
			if (x < map->map_x - 1)
			{
				setup_point_data(map, x, y, 1);
				draw_projected_line(map);
			}
			if (y < map->map_y - 1)
			{
				setup_point_data(map, x, y, 0);
				setup_point_data(map, x, y, 2);
				draw_projected_line(map);
			}
		}
	}
}
