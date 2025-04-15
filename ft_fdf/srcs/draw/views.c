/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   views.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:42:13 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 13:56:07 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*
Permet de calculer l'angle de projection
Permet de calculer la position après projection iso
	- x1 = (x - y) * cos(30°)
	- y1 = (x + y) * sin(30°) - z
	- x2 = (x {+ 1} - y) * cos(30°)
	- y2 = (x {+ 1} + y) * sin(30°) - z
*/
void	project_iso(long *x, long *y, long *z, t_fdf *map)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = *x;
	tmp_y = *y;
	tmp_z = *z;
	*map = *map;
	*x = (long)((tmp_x - tmp_y) * cos(M_PI / 6));
	*y = (long)((tmp_x + tmp_y) * sin(M_PI / 6) - tmp_z * map->scale_height);
	*z = *z;
}

void	project_perspec_axe_x(double *x, double *y, double *z, t_fdf *map)
{
	double	rad_x;
	double	tmp_y;
	double	tmp_z;

	rad_x = map->angle_x * M_PI / 180.0;
	tmp_y = (*y) * cos(rad_x) - (*z) * sin(rad_x);
	tmp_z = (*y) * sin(rad_x) + (*z) * cos(rad_x);
	*x = *x;
	*y = tmp_y;
	*z = tmp_z;
}

void	project_perspec_axe_y(double *x, double *y, double *z, t_fdf *map)
{
	double	rad_y;
	double	tmp_x;
	double	tmp_z;

	rad_y = map->angle_y * M_PI / 180.0;
	tmp_z = (*z) * cos(rad_y) - (*x) * sin(rad_y);
	tmp_x = (*z) * sin(rad_y) + (*x) * cos(rad_y);
	*x = tmp_x;
	*y = *y;
	*z = tmp_z;
}

void	project_perspec_axe_z(double *x, double *y, double *z, t_fdf *map)
{
	double	rad_z;
	double	tmp_x;
	double	tmp_y;

	rad_z = map->angle_z * M_PI / 180.0;
	tmp_x = (*x) * cos(rad_z) - (*y) * sin(rad_z);
	tmp_y = (*x) * sin(rad_z) + (*y) * cos(rad_z);
	*x = tmp_x;
	*y = tmp_y;
	*z = *z;
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
void	project_perspec(long *x, long *y, long *z, t_fdf *map)
{
	double	px;
	double	py;
	double	pz;

	px = *x;
	py = *y;
	pz = *z * map->scale_height;
	project_perspec_axe_x(&px, &py, &pz, map);
	project_perspec_axe_y(&px, &py, &pz, map);
	project_perspec_axe_z(&px, &py, &pz, map);
	*x = (long)px;
	*y = (long)py;
	*z = (long)pz;
}
