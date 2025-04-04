# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "fdf.h"
# include "../Lib/Libft/libft.h"

/*
Events: When leaving the window
*/
static int	end_program(t_fdf *map)
{
	if (!map)
		return (0);
	mlx_destroy_image(map->mlx, map->img);
	mlx_destroy_window(map->mlx, map->win);
	free(map);

	exit(0);
	return (0);
}

void	fdf_s_p(t_fdf *map, int x, int y, char *str)
{
	mlx_string_put(map->mlx, map->win, x, y, 0xFFFFFF, str);
}


void	hud(t_fdf *map)
{
	int	text_x;

	text_x = (map->screen_W / 2) - (25 * 7 / 2);
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
	fdf_s_p(map, 20, 80, ft_strjoin("Depth: ", ft_itoa((int)(map->scale))));
	fdf_s_p(map, 20, 100, ft_strjoin("Scale height: ", ft_itoa(scale_h)));
	fdf_s_p(map, 20, 120, ft_strjoin("Rotation x: ", x_axe));
	fdf_s_p(map, 20, 140, ft_strjoin("Rotation y: ", y_axe));
	fdf_s_p(map, 20, 160, ft_strjoin("Rotation z: ", z_axe));
	fdf_s_p(map, 20, 180, ft_strjoin("Position x: ", ft_itoa(map->pos_x)));
	fdf_s_p(map, 20, 200, ft_strjoin("Position y: ", ft_itoa(map->pos_y)));
}

void	hud_key(t_fdf *map)
{
	fdf_s_p(map, 20, map->screen_H - 220, "Exit: Escape key");
	fdf_s_p(map, 20, map->screen_H - 200, "View: O(persp) and P (iso)");
	fdf_s_p(map, 20, map->screen_H - 180, "Scale height: T and G");
	fdf_s_p(map, 20, map->screen_H - 160, "Depth: R and F");
	fdf_s_p(map, 20, map->screen_H - 140, "Rotation x: A and D");
	fdf_s_p(map, 20, map->screen_H - 120, "Rotation y: W and S");
	fdf_s_p(map, 20, map->screen_H - 100, "Rotation z: Q and E");
	fdf_s_p(map, 20, map->screen_H - 80, "move x and y: arrow keys");
}


/*
'P' key - isometric view
'O' key - perspective view
'T' key - increase scale height
'G' key - decrease scale height
'R' key - increase depth
'F' key - decrease depth
*/
int	key_pressed(int key, t_fdf *map)
{
	if (key == 65307)
		end_program(map);
	else if (key == 112)
		map->view_type = 0;
	else if (key == 111)
		map->view_type = 1;
	else if (key == 116)
		map->scale_height += 0.01;
	else if (key == 103)
		map->scale_height -= 0.01;
	else if (key == 114)
		map->scale += 1;
	else if (key == 102)
		map->scale -= 1;
	else
		key_pressed_mouvement(key, map);
	return (0);
}

/*
'UP' key - decrease Y position
'DOWN' key - increase Y position
'LEFT' key - decrease X position
'RIGHT' key - increase X position
'A' key - rotate up (X-axis)
'D' key - rotate down (X-axis)
'W' key - rotate left (Y-axis)
'S' key - rotate right (Y-axis)
'Q' key - rotate counterclockwise (Z-axis)
'E' key - rotate clockwise (Z-axis)
*/
void key_pressed_mouvement(int key, t_fdf *map)
{
	if (key == 65362)
		map->pos_y -= 20;
	else if (key == 65364)
		map->pos_y += 20;
	else if (key == 65361)
		map->pos_x -= 20;
	else if (key == 65363)
		map->pos_x += 20;
	else if (key == 97)
		map->angle_y -= 5;
	else if (key == 100)
		map->angle_y += 5;
	else if (key == 119)
		map->angle_x += 5;
	else if (key == 115)
		map->angle_x -= 5;
	else if (key == 113)
		map->angle_z -= 5;
	else if (key == 101)
		map->angle_z += 5;
}

int	draw(t_fdf *map)
{
	if (map->img)
		mlx_destroy_image(map->mlx, map->img);
	map->img = mlx_new_image(map->mlx, map->screen_W, map->screen_H);
	map->img_addr = mlx_get_data_addr(map->img, &(map->img_bits_per_pixel), &(map->img_line_length), &(map->img_endian));

	draw_backg(map, trgb_to_int(255, 0, 0, 0));
	draw_map(map);
	//printf("Rotation: (%f, %f, %f)\n", map->angle_x, map->angle_y, map->angle_z);
	//draw_line(map, map->screen_W / 2, 0, map->screen_W / 2, map->screen_H, 0xFF0000, 0x00FF00);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	hud(map);
	//printf("Rotation: (%d)\n", map->map_data[0][0]);
	return (0);
}


/*
42: 42.fdf
Little Montain: 42.fdf
Semi-Flat: pylone.fdf
Big: julia.fdf
Pentenegpos:

*/
int	main(int argc, char *argv[])
{
	t_fdf	*map;

	if(argc < 2)
	{
		ft_putstr_fd("Usage : ./fdf <filename>\n", 2);
		return (1);
	}
	map = malloc(sizeof(t_fdf));
	if (!map)
		exit(-1);
	map->coord = malloc(sizeof(t_coord));
	if (!map->coord)
		exit(-1);
	map->pos_x = 0;
	map->pos_y = 0;
	map->screen_W = 1600;
	map->screen_H = 2000;
	map->angle_x = 0;
	map->angle_y = 0;
	map->angle_z = 0;
	map->view = 1.0;
	map->scale = 60;
	map->scale_height = 0.08;
	map->view_type = 0;

	map->mlx = mlx_init(); // Initialize the connection to the display
	map->win = mlx_new_window(map->mlx, map->screen_W, map->screen_H, "FdF - vmeessen");  // Create a window
	map_parsing(map, argv[1]); // Parse the map file and fill the map structure
	mlx_hook(map->win, 17, 0, end_program, map);
	mlx_hook(map->win, 2, 1L << 0, key_pressed, map);
	mlx_loop_hook(map->mlx, draw, map);
	draw(map); // Draw the initial state of the map
	mlx_loop(map->mlx);  // Start the event loop
	free(map);
   	return 0;
}
