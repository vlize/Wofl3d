/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_raycasting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 09:02:20 by vlize             #+#    #+#             */
/*   Updated: 2015/11/10 09:02:21 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static void	ft_floor_ceiling0(int *i, intmax_t *y, double *p1, t_env *env)
{
	ft_window_limits(&y[0], &y[1]);
	if (env->ret[2] && (env->ret[2]->type == 'f'))
		ft_set_tex_f(i, y, p1, env);
	else if (i[7] >= 0)
		ft_set_pixel((y[1] * WIDTH + i[0]), (i[9] * WIDTH + i[0]), i[7], env);
	else
		ft_set_skybox(i[0], y[1], i[9], env);
	if (env->ret[1] && (env->ret[1]->type == 'c'))
		ft_set_tex_c(i, y, p1, env);
	else if (i[6] >= 0)
		ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
	else
		ft_set_skybox(i[0], i[8], y[0], env);
}

void		ft_wall(int *i, double *p1, t_env *env)
{
	intmax_t	y[4];
	double		k[2];

	k[0] = env->p[0] - p1[2];
	k[1] = env->p[1] - p1[3];
	if (!k[0] && !k[1])
		return ;
	k[0] = hypot(k[0], k[1]) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	y[2] = y[0];
	y[3] = y[1] - y[0];
	ft_floor_ceiling0(i, y, p1, env);
	if (env->ret[0]->type == 'w')
		ft_set_texture(i, y, env);
	else
		ft_set_pixel((y[0] * WIDTH + i[0]), (y[1] * WIDTH + i[0]), i[5], env);
}

void		ft_floor_ceiling(int *i, double *p1, t_env *env)
{
	intmax_t	y[2];
	double		k[2];

	k[0] = env->p[0] - p1[2];
	k[1] = env->p[1] - p1[3];
	if (!k[0] && !k[1])
		return ;
	k[0] = hypot(k[0], k[1]) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	ft_floor_ceiling0(i, y, p1, env);
	i[9] = y[1];
	i[8] = y[0];
}

int			ft_cast0_x(int *i, double *p1, double *k, t_env *env)
{
	if (i[2] > i[4])
		p1[3] = i[2] * BLOCK_SIZE;
	else
		p1[3] = i[4] * BLOCK_SIZE;
	p1[2] = (p1[3] - k[1]) / k[0];
	if (ft_ray_cast(i, &p1[2], env))
		return (1);
	else
		ft_floor_ceiling(i, p1, env);
	return (0);
}

int			ft_cast0_y(int *i, double *p1, double *k, t_env *env)
{
	if (i[1] > i[3])
		p1[2] = i[1] * BLOCK_SIZE;
	else
		p1[2] = i[3] * BLOCK_SIZE;
	p1[3] = (p1[2] - k[1]) / k[0];
	if (ft_ray_cast(i, &p1[2], env))
		return (1);
	else
		ft_floor_ceiling(i, p1, env);
	return (0);
}
