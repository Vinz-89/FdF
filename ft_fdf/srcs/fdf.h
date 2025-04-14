/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:58:42 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/14 13:58:42 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# include <stdlib.h> // malloc free..
# include <unistd.h> // write
//# include <stdlib.h>
# include <fcntl.h> //
# include <math.h>

# include <stdio.h>

typedef struct s_coord
{
	int	x1;
	int	y1;
	int	z1;
	int	x2;
	int	y2;
	int	z2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	color1;
	int	color2;
}	t_coord;

typedef struct s_fdf
{
	float	angle_x;
	float	angle_y;
	float	angle_z;
	int		scale;
	float	scale_height;
	int		view_type;
	int		map_x;
	int		map_y;
	int		map_min_z;
	int		map_max_z;
	t_coord	*coord;

	void	*mlx;
	void	*win;
	void	*img;
	int		screen_w;
	int		screen_h;
	float	pos_x;
	float	pos_y;
	int		**map_data;

	int		img_bits_per_pixel;
	int		img_line_length;
	int		img_endian;
	char	*img_addr;
}		t_fdf;

void	map_parsing(t_fdf *map, char *filename);
void	free_map_data(t_fdf *map);

int		trgb_to_int(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

int		interpolate_color(int color1, int color2, double ratio);
int		calculate_color(int z, int min_z, int max_z);

void	put_pixel(t_fdf *map, int p_x, int p_y, int color);
void	draw_backg(t_fdf *map, int color);
void	draw_line(t_fdf *map, t_coord *coord, int color1, int color2);

void	update_line_position(t_coord *coord, int *err);

void	draw_map(t_fdf *map);

void	project_iso(int *x, int *y, int *z, t_fdf *map);
void	project_perspec(int *x, int *y, int *z, t_fdf *map);

void	hud(t_fdf *map);
void	hud_data(t_fdf *map);
void	hud_key(t_fdf *map);
int		key_pressed(int key, t_fdf *map);
void	key_pressed_mouvement(int key, t_fdf *map);
int		draw(t_fdf *map);

#endif
