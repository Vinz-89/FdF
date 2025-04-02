# include "fdf.h"


void	put_pixel(t_fdf *map, int p_x, int p_y, int color)
{
	int		i;

   if (p_x < 0 || p_x >= map->screen_W || p_y < 0 || p_y >= map->screen_H) // Prevent overflow
      return;
	i = (p_x * map->img_bits_per_pixel / 8) + (p_y * map->img_line_length);
	map->img_addr[i] = get_b(color);
	map->img_addr[++i] = get_g(color);
	map->img_addr[++i] = get_r(color);
   map->img_addr[++i] = get_t(color);
}

void	draw_backg(t_fdf *map, int color)
{
	int	x;
	int	y;

	y = 0;
	while (++y < map->screen_H)
	{
		x = 0;
		while (++x < map->screen_W)
      {
			put_pixel(map, x, y, color);
      }
	}
}


//#define SCALE 50  // Adjust for zoom

/*
Projection 3d en 2d avec une projection isométrique
   - x1 = (x - y) * cos(30°)
   - y1 = (x + y) * sin(30°) - z
   - x2 = (x + 1 - y) * cos(30°)
   - y2 = (x + 1 + y) * sin(30°) - z
   - screenY=(x+y)∗scale
   - screenX=(x−y)∗scale
*/


void draw_map(t_fdf *map)
{
    int y = 0;
    int min_z = map->map_min_z; // Minimum height in the map
    int max_z = map->map_max_z; // Maximum height in the map

    while (y < map->map_y)
    {
        int x = 0;
        while (x < map->map_x)
        {
            if (!map->map_data[y] || !map->map_data) {
                printf("Error: map_data[%d][%d] is NULL!\n", y, x);
                return;
            }

            // Calcul des coordonnées avant projection
            int x1 = (x - map->map_x / 2) * map->scale;
            int y1 = (y - map->map_y / 2) * map->scale;
            int z1 = map->map_data[y][x] * map->scale / 10;

            // Calcul de la couleur en fonction de la hauteur
            double ratio = (double)(map->map_data[y][x] - min_z) / (max_z - min_z);
            int color = interpolate_color(0x00FF00, 0xFF00FF, ratio);

            // Projection isométrique
            project_iso(&x1, &y1, &z1, map);

            // Décalage pour centrer l'image et prendre en compte les mouvements
            x1 += (map->screen_W / 2) + map->pos_x;
            y1 += (map->screen_H / 2) + map->pos_y;

            if (x < map->map_x - 1) // Dessiner une ligne horizontale
            {
                int x2 = ((x + 1) - map->map_x / 2) * map->scale;
                int y2 = (y - map->map_y / 2) * map->scale;
                int z2 = map->map_data[y][x + 1] * map->scale / 10;

                // Calcul de la couleur pour le deuxième point
                double ratio2 = (double)(map->map_data[y][x + 1] - min_z) / (max_z - min_z);
                int color2 = interpolate_color(0x00FF00, 0xFF00FF, ratio2);

                project_iso(&x2, &y2, &z2, map);
                x2 += (map->screen_W / 2) + map->pos_x;
                y2 += (map->screen_H / 2) + map->pos_y;

                draw_line(map, x1, y1, x2, y2, color, color2);
            }

            if (y < map->map_y - 1) // Dessiner une ligne verticale
            {
                int x2 = (x - map->map_x / 2) * map->scale;
                int y2 = ((y + 1) - map->map_y / 2) * map->scale;
                int z2 = map->map_data[y + 1][x] * map->scale / 10;

                // Calcul de la couleur pour le deuxième point
                double ratio2 = (double)(map->map_data[y + 1][x] - min_z) / (max_z - min_z);
                int color2 = interpolate_color(0x00FF00, 0xFF00FF, ratio2);

                project_iso(&x2, &y2, &z2, map);
                x2 += (map->screen_W / 2) + map->pos_x;
                y2 += (map->screen_H / 2) + map->pos_y;

                draw_line(map, x1, y1, x2, y2, color, color2);
            }

            x++; // Incrémentation de x
        }
        y++; // Incrémentation de y
    }
}

void draw_line(t_fdf *map, int x0, int y0, int x1, int y1, int color1, int color2)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    int length = (dx > dy) ? dx : dy;
    int step = 0; // Step counter for color interpolation

    while (x0 != x1 || y0 != y1)
    {
      double ratio = (double)step / length;
      int color = interpolate_color(color1, color2, ratio);

      put_pixel(map, x0, y0, color);
      int e2 = err * 2;
      if (e2 > -dy) { err -= dy; x0 += sx; }
      if (e2 < dx) { err += dx; y0 += sy; }
      step++;
    }
}

/*
Permet de calculer l'angle de projection

*/
void project_iso(int *x, int *y, int *z, t_fdf *map)
{
    double px = *x, py = *y, pz = *z;

    // Convert angles from degrees to radians
    double rad_x = map->angle_x * M_PI / 180.0;
    double rad_y = map->angle_y * M_PI / 180.0;
    double rad_z = map->angle_z * M_PI / 180.0;

    // Perform rotations in sequence: Z → X → Y
    
    // Rotation around X-axis (affects Y and Z)
    py = py * cos(rad_x) - pz * sin(rad_x);
    pz = py * sin(rad_x) + pz * cos(rad_x);

    // Rotation around Y-axis (affects X and Z)
    px = px * cos(rad_y) + pz * sin(rad_y);
    pz = pz * cos(rad_y) - px * sin(rad_y);

    // Rotation around Z-axis (affects X and Y)
    *x = (int)(px * cos(rad_z) - py * sin(rad_z));
    *y = (int)(px * sin(rad_z) + py * cos(rad_z));
    *z = (int)pz; // Keep depth for further use
}
