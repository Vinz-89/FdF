/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:50:17 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/14 14:50:17 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include "fdf.h"
#include "../Lib/Libft/libft.h"

/*
Events: When leaving the window
*/
static int	end_program(t_fdf *map)
{
	if (!map)
		return (0);
	if (map->img && map->img)
		mlx_destroy_image(map->mlx, map->img);
	if (map->img && map->win)
		mlx_destroy_window(map->mlx, map->win);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	free_map_data(map);
	if (map->coord)
		free(map->coord);
	free(map);
	exit(0);
	return (0);
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
void	key_pressed_mouvement(int key, t_fdf *map)
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

void	setup_var(t_fdf *map)
{
	map->coord = malloc(sizeof(t_coord));
	if (!map->coord)
	{
		free(map);
		exit(-1);
	}
	map->pos_x = 0;
	map->pos_y = 0;
	map->screen_w = 1600;
	map->screen_h = 2000;
	map->angle_x = 0;
	map->angle_y = 0;
	map->angle_z = 0;
	map->scale = 60;
	map->scale_height = 0.08;
	map->view_type = 0;
	map->win = NULL;
	map->mlx = NULL;
	map->img = NULL;
	map->img_addr = NULL;
	map->map_data = NULL;
}

/*
42: 42.fdf
Little Montain: 42.fdf
Semi-Flat: pylone.fdf
Big: julia.fdf
*/
int	main(int argc, char *argv[])
{
	t_fdf	*map;

	if (argc < 2)
	{
		ft_putstr_fd("Usage : ./fdf <filename.fdf>\n", 2);
		return (1);
	}
	map = malloc(sizeof(t_fdf));
	if (!map)
		exit(-1);
	setup_var(map);
	map_parsing(map, argv[1]);
	fix_scale_height(map);
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, map->screen_w, map->screen_h,
			"FdF - vmeessen");
	mlx_hook(map->win, 17, 0, end_program, map);
	mlx_hook(map->win, 2, 1L << 0, key_pressed, map);
	mlx_loop_hook(map->mlx, draw, map);
	draw(map);
	mlx_loop(map->mlx);
	end_program(map);
	return (0);
}
