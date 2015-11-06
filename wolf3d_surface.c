/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_surface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 09:19:18 by vlize             #+#    #+#             */
/*   Updated: 2015/11/06 09:19:19 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	ft_wall(int *i, double *p1, t_env *env)
{
	intmax_t	y[2];
	double		k[2];

	k[0] = env->p[0] - p1[0];
	k[1] = env->p[1] - p1[1];
	if (!k[0] && !k[1])
		return ;
	k[0] = hypot((env->p[0] - p1[0]), (env->p[1] - p1[1])) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	ft_window_limits(&y[0], &y[1]);
	ft_set_pixel((y[0] * WIDTH + i[0]), (y[1] * WIDTH + i[0]), i[5], env);
	ft_set_pixel((y[1] * WIDTH + i[0]), (i[9] * WIDTH + i[0]), i[7], env);
	if (i[6] >= 0)
		ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
	else
		ft_set_skybox(i[0], i[8], y[0], env);
}

void	ft_floor_ceiling(int *i, double *p1, t_env *env)
{
	intmax_t	y[2];
	double		k[2];

	k[0] = env->p[0] - p1[0];
	k[1] = env->p[1] - p1[1];
	if (!k[0] && !k[1])
		return ;
	k[0] = hypot(k[0], k[1]) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	ft_window_limits(&y[0], &y[1]);
	ft_set_pixel((y[1] * WIDTH + i[0]), (i[9] * WIDTH + i[0]), i[7], env);
	if (i[6] >= 0)
		ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
	else
		ft_set_skybox(i[0], i[8], y[0], env);
	i[9] = y[1];
	i[8] = y[0];
}
