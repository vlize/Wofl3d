/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 08:37:40 by vlize             #+#    #+#             */
/*   Updated: 2015/10/23 08:37:41 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "wolf3d_color.h"

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
	ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
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
	ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
	i[9] = y[1];
	i[8] = y[0];
}

int		ft_cast0_x(int *i, double *p1, double *k, t_env *env)
{
	if (i[2] > i[4])
		p1[5] = i[2] * BLOCK_SIZE;
	else
		p1[5] = i[4] * BLOCK_SIZE;
	p1[4] = (p1[5] - k[1]) / k[0];
	if (p1[4] == p1[2])
		return (0);
	if (ft_ray_cast(i, &p1[4], env))
		return (1);
	else
		ft_floor_ceiling(i, &p1[4], env);
	return (0);
}

int		ft_cast0_y(int *i, double *p1, double *k, t_env *env)
{
	if (i[1] > i[3])
		p1[4] = i[1] * BLOCK_SIZE;
	else
		p1[4] = i[3] * BLOCK_SIZE;
	p1[5] = (p1[4] - k[1]) / k[0];
	if (p1[5] == p1[3])
		return (0);
	if (ft_ray_cast(i, &p1[4], env))
		return (1);
	else
		ft_floor_ceiling(i, &p1[4], env);
	return (0);
}
