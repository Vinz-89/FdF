/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:18:48 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 15:27:45 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*
Put pixel on screen if it is in the range of the screen
*/
void	put_pixel(t_fdf *map, long p_x, long p_y, int color)
{
	int		i;

	//printf("%ld %ld\n\n", (long)map->screen_w, (long)map->screen_h);
	if (p_x < 0 || p_x >= (long)map->screen_w || p_y < 0 || p_y >= (long)map->screen_h)
		return ;
	//printf("%ld %ld\n", p_x, p_y);
	i = (p_x * map->img_bits_per_pixel / 8) + (p_y * map->img_line_length);
	map->img_addr[i] = get_b(color);
	map->img_addr[++i] = get_g(color);
	map->img_addr[++i] = get_r(color);
	map->img_addr[++i] = get_t(color);
}

/*
setup background color
*/
void	draw_backg(t_fdf *map, int color)
{
	int	x;
	int	y;

	y = 0;
	while (++y < map->screen_h)
	{
		x = 0;
		while (++x < map->screen_w)
		{
			put_pixel(map, x, y, color);
		}
	}
}

static void	initialize_line(t_coord *coord, int *err, int *length)
{
	coord->dx = ft_abs(coord->x2 - coord->x1);
	coord->dy = ft_abs(coord->y2 - coord->y1);
	if (coord->x1 < coord->x2)
		coord->sx = 1;
	else
		coord->sx = -1;
	if (coord->y1 < coord->y2)
		coord->sy = 1;
	else
		coord->sy = -1;
	*err = coord->dx - coord->dy;
	if (coord->dx > coord->dy)
		*length = coord->dx;
	else
		*length = coord->dy;
}

void	update_line_position(t_coord *coord, int *err)
{
	int	e2;

	e2 = *err * 2;
	if (e2 > -coord->dy)
	{
		*err -= coord->dy;
		coord->x1 += coord->sx;
	}
	if (e2 < coord->dx)
	{
		*err += coord->dx;
		coord->y1 += coord->sy;
	}
}

/*
dessine une ligne entre 2 points et avec une interpolation de la couleur
*/
void	draw_line(t_fdf *map, t_coord *coord, int color1, int color2)
{
	int	err;
	int	length;
	int	step;
	int	color;

	initialize_line(coord, &err, &length);
	step = 0;
	while (coord->x1 != coord->x2 || coord->y1 != coord->y2)
	{
		color = interpolate_color(color1, color2, (double)step / length);
		put_pixel(map, coord->x1, coord->y1, color);
		update_line_position(coord, &err);
		step++;
	}
}
