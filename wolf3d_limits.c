/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_limits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 13:43:39 by vlize             #+#    #+#             */
/*   Updated: 2015/10/23 13:43:52 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_map_limits(double *p, t_map *map)
{
	if (p[0] < 0)
		p[0] = 0;
	else if (p[0] >= map->xmax)
		p[0] = map->xmax - 1;
	if (p[1] < 0)
		p[1] = 0;
	else if (p[1] >= map->ymax)
		p[1] = map->ymax - 1;
}

void	ft_window_limits(int *y, int *ymax)
{
	if ((*y) < 0)
		(*y) = 0;
	if ((*ymax) >= HEIGHT)
		(*ymax) = HEIGHT - 1;
}

int		ft_limit_xy(int *i, t_env *env)
{
	if ((i[1] < 0) || (i[1] >= env->map->xblock))
		return (0);
	if ((i[2] < 0) || (i[2] >= env->map->yblock))
		return (0);
	return (1);
}

int		ft_find_i(int i1, int i2)
{
	if (i1 > i2)
		return (i1);
	return (i2);
}
