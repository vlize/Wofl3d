/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/28 15:54:19 by vlize             #+#    #+#             */
/*   Updated: 2015/09/28 15:54:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "wolf3d_color.h"

void	ft_raycasting_loop(t_env *env)
{
	double	p1[6];
	double	k[4];
	int		i[10];

	i[5] = 1;
	i[6] = 1;
	i[7] = W8;
	i[8] = W9;
	i[0] = 0;
	while (i[0] < WIDTH)
	{
		k[0] = env->map->zrot - env->angle[i[0]];
		p1[0] = env->hypo[i[0]] * cos(k[0]) + env->p[0];
		p1[1] = env->hypo[i[0]] * sin(k[0]) + env->p[1];
		p1[2] = env->tall + env->p[2];
		k[2] = p1[0] - env->p[0];
		k[3] = p1[1] - env->p[1];
		if (fabs(k[2]) >= fabs(k[3]))
			ft_trace_x(i, p1, k, env);
		else
			ft_trace_y(i, p1, k, env);
		i[0]++;
	}
}
