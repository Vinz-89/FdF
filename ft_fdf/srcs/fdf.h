#ifndef FDF_H
# define FDF_H


# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# include <unistd.h>
//# include <stdlib.h>
# include <fcntl.h>
# include <fcntl.h>
# include <math.h>


# include <stdio.h>
# include <stdlib.h>

typedef struct s_fdf
{
	int screen_W;
	int screen_H;

	float angle_x;  // Rotation autour de l'axe X
	float angle_y;  // Rotation autour de l'axe Y
	float angle_z;  // Rotation autour de l'axe Z (rotation de la vue isométrique)

	int scale;
	float scale_height;

	int view_type; // 0 = isométrique, 1 = perspective

	int map_x;
	int map_y;

	int map_min_z;
	int map_max_z;


	void	*mlx;
	void	*win;
	float	pos_x;
	float	pos_y;
	float	view;

	int	**map_data;

	void	*img;
	int	img_bits_per_pixel;
	int	img_line_length;
	int	img_endian;
	char	*img_addr;
}		t_fdf;

void	put_pixel(t_fdf *map, int p_x, int p_y, int color);
void	map_parsing(t_fdf *map, char *filename);
void	draw_backg(t_fdf *map, int color);
int   trgb_to_int(int t, int r, int g, int b);
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);

void draw_map(t_fdf *map);
void draw_line(t_fdf *map, int x0, int y0, int x1, int y1, int color1, int color2);
void project_iso(int *x, int *y, int *z, t_fdf *map);
void project_perspec(int *x, int *y, int *z, t_fdf *map);

int interpolate_color(int color1, int color2, double ratio);


#endif