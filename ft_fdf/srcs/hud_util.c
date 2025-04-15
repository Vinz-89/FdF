/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:43:08 by vmeessen          #+#    #+#             */
/*   Updated: 2025/04/15 14:44:47 by vmeessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../Lib/Libft/libft.h"

void	fdf_s_p(t_fdf *map, int x, int y, char *str)
{
	mlx_string_put(map->mlx, map->win, x, y, 0xFFFFFF, str);
}

void	fdf_s_p_l(t_fdf *map, int y, char *str1, char *str2)
{
	char	*str;

	str = ft_strjoin(str1, str2);
	mlx_string_put(map->mlx, map->win, 20, y, 0xFFFFFF, str);
	free(str);
}

void	fdf_s_p_l_n(t_fdf *map, int y, char *str1, int nb)
{
	char	*str;
	char	*nbstr;

	nbstr = ft_itoa(nb);
	str = ft_strjoin(str1, nbstr);
	free(nbstr);
	mlx_string_put(map->mlx, map->win, 20, y, 0xFFFFFF, str);
	free(str);
}
