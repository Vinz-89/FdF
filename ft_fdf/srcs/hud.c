/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:52:39 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 15:24:44 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../Lib/Libft/libft.h"

void	hud(t_fdf *map)
{
	int	text_x;

	text_x = (map->screen_w / 2) - (25 * 7 / 2);
	fdf_s_p(map, text_x, 20, "...:: FdF - vmeessen ::..");
	hud_data(map);
	hud_key(map);
}

void	hud_data(t_fdf *map)
{
	int		scale_h;
	char	*x_axe;
	char	*y_axe;
	char	*z_axe;

	scale_h = map->scale_height * 100;
	x_axe = ft_itoa((int)map->angle_x % 360);
	y_axe = ft_itoa((int)map->angle_y % 360);
	z_axe = ft_itoa((int)map->angle_z % 360);
	fdf_s_p_l_n(map, 80, "Depth: ", map->scale);
	fdf_s_p_l_n(map, 100, "Scale height: ", scale_h);
	fdf_s_p_l(map, 120, "Rotation x: ", x_axe);
	fdf_s_p_l(map, 140, "Rotation y: ", y_axe);
	fdf_s_p_l(map, 160, "Rotation z: ", z_axe);
	fdf_s_p_l_n(map, 180, "Position x: ", (int)map->pos_x);
	fdf_s_p_l_n(map, 200, "Position y: ", (int)map->pos_y);
	free(x_axe);
	free(y_axe);
	free(z_axe);
}

void	hud_key(t_fdf *map)
{
	fdf_s_p(map, 20, map->screen_h - 220, "Exit: Escape key");
	fdf_s_p(map, 20, map->screen_h - 200, "View: O(persp) and P (iso)");
	fdf_s_p(map, 20, map->screen_h - 180, "Scale height: T and G");
	fdf_s_p(map, 20, map->screen_h - 160, "Depth: R and F");
	fdf_s_p(map, 20, map->screen_h - 140, "Rotation x: A and D");
	fdf_s_p(map, 20, map->screen_h - 120, "Rotation y: W and S");
	fdf_s_p(map, 20, map->screen_h - 100, "Rotation z: Q and E");
	fdf_s_p(map, 20, map->screen_h - 80, "move x and y: arrow keys");
}

void	fix_scale_height(t_fdf	*map)
{
	long	value;

	value = (long)map->map_max_z;
	if (value < (long)map->map_min_z * -1)
		value = (long)map->map_min_z * -1;
	if (value > INT_MAX)
		value = INT_MAX;
	if (value == 0)
		value = 1;
	map->scale_height = 0.8 / value;
}

int	draw(t_fdf *map)
{
	if (map->img)
		mlx_destroy_image(map->mlx, map->img);
	map->img = mlx_new_image(map->mlx, map->screen_w, map->screen_h);
	map->img_addr = mlx_get_data_addr(map->img, &(map->img_bits_per_pixel),
			&(map->img_line_length), &(map->img_endian));
	draw_backg(map, trgb_to_int(255, 0, 0, 0));
	draw_map(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	hud(map);
	return (0);
}
