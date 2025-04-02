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
		return 0;
	//mlx_destroy_image(map->mlx, map->img);
	mlx_destroy_window(map->mlx, map->win);
	free(map);

	exit(0);
	return 0;
}

void fdf_string_put(t_fdf *map, int x, int y, char *str)
{
	mlx_string_put(map->mlx, map->win, x, y, 0xFFFFFF, str);
}





void	hud(t_fdf *map)
{
	int	char_width;
	int	x_axe;
	int	y_axe;
	int	z_axe;
	int	text_x;

	char_width = 7;
	x_axe = map->angle_x;
	y_axe = map->angle_y;
	z_axe = map->angle_z;
	text_x = (map->screen_W / 2) - (25 * char_width / 2);
	fdf_string_put(map, text_x, 20, "FdF - vmeessen");

	mlx_string_put(map->mlx, map->win, text_x, 20, 0xFFFFFF, "...:: FdF - vmeessen ::..");
	fdf_string_put(map, 20, 40, ft_strjoin("Scale: ", ft_itoa(map->scale)));
	mlx_string_put(map->mlx, map->win, 20, 80, 0xFFFFFF, ft_strjoin("Depth: ", ft_itoa(map->scale)));
	fdf_string_put(map, 20, 100, ft_strjoin("Scale height: ", ft_itoa((int)(map->scale_height*100))));
	mlx_string_put(map->mlx, map->win, 20, 100, 0xFFFFFF, ft_strjoin("Scale height: ", ft_itoa((int)(map->scale_height*100))));
	fdf_string_put(map, 20, 120, ft_strjoin("Rotation x: ", ft_itoa(abs(x_axe%360))));
	mlx_string_put(map->mlx, map->win, 20, 120, 0xFFFFFF, ft_strjoin("Rotation x: ", ft_itoa(abs(x_axe%360))));
	fdf_string_put(map, 20, 140, ft_strjoin("Rotation y: ", ft_itoa(abs(y_axe%360))));
	mlx_string_put(map->mlx, map->win, 20, 140, 0xFFFFFF, ft_strjoin("Rotation y: ", ft_itoa(abs(y_axe%360))));
	fdf_string_put(map, 20, 160, ft_strjoin("Rotation z: ", ft_itoa(abs(z_axe%360))));
	mlx_string_put(map->mlx, map->win, 20, 160, 0xFFFFFF, ft_strjoin("Rotation z: ", ft_itoa(abs(z_axe%360))));
	fdf_string_put(map, 20, 180, ft_strjoin("Position x: ", ft_itoa(map->pos_x)));
	mlx_string_put(map->mlx, map->win, 20, 180, 0xFFFFFF, ft_strjoin("Position x: ", ft_itoa(map->pos_x)));
	fdf_string_put(map, 20, 200, ft_strjoin("Position y: ", ft_itoa(map->pos_y)));
	mlx_string_put(map->mlx, map->win, 20, 200, 0xFFFFFF, ft_strjoin("Position y: ", ft_itoa(map->pos_y)));

	fdf_string_put(map, 20, map->screen_H - 220, "Exit: Escape key");
	fdf_string_put(map, 20, map->screen_H - 200, "View: O(prespec) and P (iso)");
	fdf_string_put(map, 20, map->screen_H - 180, "Scale height: T and G");
	fdf_string_put(map, 20, map->screen_H - 160, "Depth: R and F");
	fdf_string_put(map, 20, map->screen_H - 140, "Rotation x: A and D");
	fdf_string_put(map, 20, map->screen_H - 120, "Rotation y: W and S");
	fdf_string_put(map, 20, map->screen_H - 100, "Rotation z: Q and E");
	fdf_string_put(map, 20, map->screen_H - 80, "Direction x: arrow keys");
}


int	key_pressed(int key, t_fdf *map)
{
	printf("->%d\n",key);
	// Movement
	if (key == 65362) // UP arrow key
		map->pos_y -= 20;
	else if (key == 65364) // DOWN arrow key
		map->pos_y += 20;
	else if (key == 65361) // LEFT arrow key
		map->pos_x -= 20;
	else if (key == 65363) // RIGHT arrow key
		map->pos_x += 20;

	// Rotation
	else if (key == 97) // 'A' key - Rotate up (X-axis)
		map->angle_y -= 5;
	else if (key == 100) // 'D' key - Rotate down (X-axis)
		map->angle_y += 5;
	else if (key == 119) // 'W' key - Rotate left (Y-axis)
		map->angle_x += 5;
	else if (key == 115) // 'S' key - Rotate right (Y-axis)
		map->angle_x -= 5;
	else if (key == 113)  // 'Q' key - Rotate counterclockwise (Z-axis)
		map->angle_z -= 5;
	else if (key == 101) // 'E' key - Rotate clockwise (Z-axis)
		map->angle_z += 5;
	// Scale
	else if (key == 114)  // 'R' key - increase depth
		map->scale += 1;
	else if (key == 102)  // 'F' key - decrease depth
		map->scale -= 1;
	else if (key == 116)  // 'T' key - increase scale height
		map->scale_height += 0.01;
	else if (key == 103)  // 'G' key - decrease scale height
		map->scale_height -= 0.01;

	// View
	else if (key == 112)  // 'P' key - isometric view
		map->view_type = 0;
	else if (key == 111)  // 'O' key - perspective view
		map->view_type = 1;

	else if (key == 65307)
		end_program(map);

	return (0);
}


int	draw(t_fdf *map)
{
	if(map->img)
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
17:DestroyNotify

Semi-Flat: pylone.fdf




le sujet donne un angle plus ou moins pour (40,-20,40)
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
