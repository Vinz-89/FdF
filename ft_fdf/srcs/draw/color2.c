/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:40:08 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 15:55:34 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	interpolate_color(int colr1, int colr2, double ratio)
{
	int	red;
	int	green;
	int	blue;

	red = ((colr2 >> 16) & 0xFF) * ratio + ((colr1 >> 16) & 0xFF) * (1 - ratio);
	green = ((colr2 >> 8) & 0xFF) * ratio + ((colr1 >> 8) & 0xFF) * (1 - ratio);
	blue = (colr2 & 0xFF) * ratio + (colr1 & 0xFF) * (1 - ratio);
	return ((red << 16) | (green << 8) | blue);
}

/*
Donne l interpolation entre deux couleur par rapport a la hauteur
*/
int	calculate_color(long z, int min_z, int max_z)
{
	double	ratio;

	if (max_z == min_z)
		ratio = 0;
	else
		ratio = (double)(z - (long)min_z) / (double)((long)max_z - (long)min_z);
	return (interpolate_color(0x00FF00, 0xFF00FF, ratio));
}
