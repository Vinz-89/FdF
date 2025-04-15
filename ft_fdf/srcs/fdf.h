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
# include <limits.h> // pour les INT_MIN/MAX

# include <stdio.h>

typedef struct s_coord
{
	long	x1;
	long	y1;
	long	z1;
	long	x2;
	long	y2;
	long	z2;
	long	dx;
	long	dy;
	long	sx;
	long	sy;
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

long	ft_atoi(const char *nptr);
long	ft_abs(long value);
void	map_parsing(t_fdf *map, char *filename);
void	free_map_data(t_fdf *map);

int		trgb_to_int(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

int		interpolate_color(int color1, int color2, double ratio);
int		calculate_color(long z, int min_z, int max_z);

void	put_pixel(t_fdf *map, long p_x, long p_y, int color);
void	draw_backg(t_fdf *map, int color);
void	draw_line(t_fdf *map, t_coord *coord, int color1, int color2);

void	update_line_position(t_coord *coord, int *err);

void	draw_map(t_fdf *map);

void	project_iso(long *x, long *y, long *z, t_fdf *map);
void	project_perspec(long *x, long *y, long *z, t_fdf *map);

void	hud(t_fdf *map);
void	hud_data(t_fdf *map);
void	hud_key(t_fdf *map);
int		key_pressed(int key, t_fdf *map);
void	key_pressed_mouvement(int key, t_fdf *map);
int		draw(t_fdf *map);

void	fix_scale_height(t_fdf	*map);
void	fdf_s_p(t_fdf *map, int x, int y, char *str);
void	fdf_s_p_l(t_fdf *map, int y, char *str1, char *str2);
void	fdf_s_p_l_n(t_fdf *map, int y, char *str1, int nb);

#endif
