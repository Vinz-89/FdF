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

void	hud(t_fdf *map)
{
	int text_length = 25;
	int char_width = 7;
	int x_axe = map->angle_x;
	int y_axe = map->angle_y;
	int z_axe = map->angle_z;

	int text_x = (map->screen_W / 2) - (text_length * char_width / 2);
	mlx_string_put(map->mlx, map->win, text_x, 20, 0xFFFFFF, "...:: FdF - vmeessen ::..");
	mlx_string_put(map->mlx, map->win, 20, 20, 0xFFFFFF, ft_strjoin("Rotation x: ", ft_itoa(x_axe)));
	mlx_string_put(map->mlx, map->win, 20, 40, 0xFFFFFF, ft_strjoin("Rotation y: ", ft_itoa(y_axe)));
	mlx_string_put(map->mlx, map->win, 20, 60, 0xFFFFFF, ft_strjoin("Rotation z: ", ft_itoa(z_axe)));

	mlx_string_put(map->mlx, map->win, 20, 120, 0xFFFFFF, ft_strjoin("Rotation x: ", ft_itoa(x_axe%360)));
	mlx_string_put(map->mlx, map->win, 20, 140, 0xFFFFFF, ft_strjoin("Rotation y: ", ft_itoa(y_axe%360)));
	mlx_string_put(map->mlx, map->win, 20, 160, 0xFFFFFF, ft_strjoin("Rotation z: ", ft_itoa(z_axe%360)));
}


int	key_pressed(int key, t_fdf *map)
{
	printf("->%d\n",key);
	if (key == 65362) // UP arrow key
		map->pos_y -= 20;
	else if (key == 65364) // DOWN arrow key
		map->pos_y += 20;
	else if (key == 65361) // LEFT arrow key
		map->pos_x -= 20;
	else if (key == 65363) // RIGHT arrow key
		map->pos_x += 20;

	else if (key == 113) // 'Q' key - Rotate up (X-axis)
		map->angle_y -= 5;
	else if (key == 100) // 'D' key - Rotate down (X-axis)
		map->angle_y += 5;
	else if (key == 122) // 'Z' key - Rotate left (Y-axis)
		map->angle_x += 5;
	else if (key == 115) // 'S' key - Rotate right (Y-axis)
		map->angle_x -= 5;
	else if (key == 97)  // 'A' key - Rotate counterclockwise (Z-axis)
		map->angle_z -= 5;
	else if (key == 101) // 'E' key - Rotate clockwise (Z-axis)
		map->angle_z += 5;
	if (key == 114)  // 'R' key - increase depth
		map->scale += 1;
	if (key == 102)  // 'F' key - decrease depth
		map->scale -= 1;

	if (key == 65307)
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
	printf("Rotation: (%f, %f, %f)\n", map->angle_x, map->angle_y, map->angle_z);
	//draw_line(map, map->screen_W / 2, 0, map->screen_W / 2, map->screen_H, 0xFF0000, 0x00FF00);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	hud(map);
	return (0);
}


/*
17:DestroyNotify

Semi-Flat: pylone.fdf




le sujet donne un angle plus ou moins pour (40,-20,40)
*/
int main() {
	t_fdf	*map;

	map = malloc(sizeof(t_fdf));
	if (!map)
		exit(-1);

	map->pos_x = 0;
	map->pos_y = 0;
	map->screen_W = 800;
	map->screen_H = 1000;
	map->angle_x = 0;
	map->angle_y = 0;
	map->angle_z = 0;
	map->view = 1.0;
	map->scale = 25;

	map->mlx = mlx_init(); // Initialize the connection to the display
	map->win = mlx_new_window(map->mlx, map->screen_W, map->screen_H, "MiniLibX Example");  // Create a window
	map_parsing(map, "test_maps/42.fdf"); // Parse the map file and fill the map structure
	mlx_hook(map->win, 17, 0, end_program, map);
	mlx_hook(map->win, 2, 1L << 0, key_pressed, map);
	mlx_loop_hook(map->mlx, draw, map);
	draw(map); // Draw the initial state of the map
	mlx_loop(map->mlx);  // Start the event loop
	free(map);
   	return 0;
}