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

// Fonction pour calculer les coordonnées projetées
void calculate_projected_coords(t_fdf *map, int *x, int *y, int *z)
{
    if (map->view_type == 0)
        project_iso(x, y, z, map);
    else
        project_perspec(x, y, z, map);

    *x += (map->screen_W / 2) + map->pos_x;
    *y += (map->screen_H / 2) + map->pos_y;
}

// Fonction pour calculer la couleur interpolée
int calculate_color(t_fdf *map, int z, int min_z, int max_z)
{
	map->map_min_z = map->map_min_z;
    double ratio = (max_z == min_z) ? 0 : (double)(z - min_z) / (max_z - min_z);
    return interpolate_color(0x00FF00, 0xFF00FF, ratio);
}

// Fonction pour dessiner une ligne entre deux points
void draw_projected_line(t_fdf *map, int x1, int y1, int z1, int x2, int y2, int z2, int min_z, int max_z)
{
    int color1 = calculate_color(map, z1, min_z, max_z);
    int color2 = calculate_color(map, z2, min_z, max_z);

    calculate_projected_coords(map, &x1, &y1, &z1);
    calculate_projected_coords(map, &x2, &y2, &z2);

    map->coord->x1 = x1;
    map->coord->y1 = y1;
    map->coord->x2 = x2;
    map->coord->y2 = y2;

    draw_line(map, map->coord, color1, color2);
}

// Fonction principale pour dessiner la carte
void draw_map(t_fdf *map)
{
    int min_z = map->map_min_z; // Minimum height in the map
    int max_z = map->map_max_z; // Maximum height in the map

    int y = 0;
    while (y < map->map_y) // Boucle pour parcourir les lignes
    {
        int x = 0;
        while (x < map->map_x) // Boucle pour parcourir les colonnes
        {
            if (!map->map_data[y] || !map->map_data)
            {
                printf("Error: map_data[%d][%d] is NULL!\n", y, x);
                return;
            }

            int x1 = (x - map->map_x / 2) * map->scale;
            int y1 = (y - map->map_y / 2) * map->scale;
            int z1 = map->map_data[y][x] * map->scale;

            if (x < map->map_x - 1)
            {
                int x2 = ((x + 1) - map->map_x / 2) * map->scale;
                int y2 = y1;
                int z2 = map->map_data[y][x + 1] * map->scale;

                draw_projected_line(map, x1, y1, z1, x2, y2, z2, min_z, max_z);
            }
            if (y < map->map_y - 1)
            {
                int x2 = x1;
                int y2 = ((y + 1) - map->map_y / 2) * map->scale;
                int z2 = map->map_data[y + 1][x] * map->scale;

                draw_projected_line(map, x1, y1, z1, x2, y2, z2, min_z, max_z);
            }

            x++; // Incrémentation de x
        }
        y++; // Incrémentation de y
    }
}

void draw_line(t_fdf *map, t_coord* coord, int color1, int color2)
{
    int dx = abs(coord->x2 - coord->x1);
    int dy = abs(coord->y2 - coord->y1);
    int sx = (coord->x1 < coord->x2) ? 1 : -1;
    int sy = (coord->y1 < coord->y2) ? 1 : -1;
    int err = dx - dy;

    int length = (dx > dy) ? dx : dy;
    int step = 0; // Step counter for color interpolation

    while (coord->x1 != coord->x2 || coord->y1 != coord->y2)
    {
      double ratio = (double)step / length;
      int color = interpolate_color(color1, color2, ratio);

      put_pixel(map, coord->x1, coord->y1, color);
      int e2 = err * 2;
      if (e2 > -dy) { err -= dy; coord->x1 += sx; }
      if (e2 < dx) { err += dx; coord->y1 += sy; }
      step++;
    }
}

/*
Permet de calculer l'angle de projection
Permet de calculer la position après projection iso
   - x1 = (x - y) * cos(30°)
   - y1 = (x + y) * sin(30°) - z
   - x2 = (x {+ 1} - y) * cos(30°)
   - y2 = (x {+ 1} + y) * sin(30°) - z
*/
void project_iso(int *x, int *y, int *z, t_fdf *map)
{
    //double px = *x, py = *y, pz = *z;
    double tmp_x = *x;
    double tmp_y = *y;
    double tmp_z = *z;

    *map = *map;

    // Rotation around Z-axis (affects X and Y)
    *x = (int)((tmp_x - tmp_y) * cos(M_PI/6));
    *y = (int)((tmp_x + tmp_y) * sin(M_PI/6) - tmp_z*map->scale_height);

    *z = *z; // Keep depth for further use
}

/*
Permet de calculer la position après projection en perspective
    - Rotation autour de l'axe X :
        - y' = y * cos(angle_x) - z * sin(angle_x)
        - z' = y * sin(angle_x) + z * cos(angle_x)
   - Rotation autour de l'axe Y :
        - z'' = z' * cos(angle_y) - x' * sin(angle_y)
        - x'' = z' * sin(angle_y) + x' * cos(angle_y)
   - Rotation autour de l'axe Z :
        - x''' = x'' * cos(angle_z) - y'' * sin(angle_z)
        - y''' = x'' * sin(angle_z) + y'' * cos(angle_z)
*/
void project_perspec(int *x, int *y, int *z, t_fdf *map)
{
    double px = *x, py = *y, pz = *z * map->scale_height;


    // Convert angles from degrees to radians
    double rad_x = map->angle_x * M_PI / 180.0;
    double rad_y = map->angle_y * M_PI / 180.0;
    double rad_z = map->angle_z * M_PI / 180.0;

    // Temporary variables for intermediate results
    double tmp_y, tmp_z, tmp_x;

    // Rotation around X-axis (affects Y and Z)
    tmp_y = py * cos(rad_x) - pz * sin(rad_x);
    tmp_z = py * sin(rad_x) + pz * cos(rad_x);
    py = tmp_y;
    pz = tmp_z;

    // Rotation around Y-axis (affects X and Z)
    tmp_z = pz * cos(rad_y) - px * sin(rad_y);
    tmp_x = pz * sin(rad_y) + px * cos(rad_y);
    px = tmp_x;
    pz = tmp_z;

    // Rotation around Z-axis (affects X and Y)
    tmp_x = px * cos(rad_z) - py * sin(rad_z);
    tmp_y = px * sin(rad_z) + py * cos(rad_z);
    px = tmp_x;
    py = tmp_y;

    // Update the original coordinates
    *x = (int)px;
    *y = (int)py;
    *z = (int)pz; // Keep depth for further use
}
