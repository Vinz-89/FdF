/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:52:39 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/14 18:04:42 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../Lib/Libft/libft.h"

void	fdf_s_p(t_fdf *map, int x, int y, char *str)
{
	mlx_string_put(map->mlx, map->win, x, y, 0xFFFFFF, str);
}

void	hud(t_fdf *map)
{
	int	text_x;

	text_x = (map->screen_w / 2) - (25 * 7 / 2);
	fdf_s_p(map, text_x, 20, "...:: FdF - vmeessen ::..");
	hud_data(map);
	hud_key(map);
}

void	fdf_s_p_l(t_fdf *map, int y, char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	mlx_string_put(map->mlx, map->win, 20, y, 0xFFFFFF, str);
	free(str);
}

void	fdf_s_p_l_n(t_fdf *map, int y, char *str1, int nb)
{
	char	*str;
	char	*nbstr;

	nbstr = ft_itoa(nb);
	str = ft_strjoin(str1, nbstr);
	free(nbstr);
	mlx_string_put(map->mlx, map->win, 20, y, 0xFFFFFF, str);
	free(str);
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
