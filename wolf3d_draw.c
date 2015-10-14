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

void	*ft_raycasting0(void *arg)
{
	t_env	*env;
	int		i[7];
	double	p1[6];
	double	k[4];

	env = (t_env *)arg;
	i[5] = 1;
	i[6] = 1;
	i[0] = WIDTH_4 - 1;
	while (i[0] >= 0)
	{
		p1[2] = (DEPTH / env->coef[i[0]]);
		p1[0] = p1[2] * cos(env->map->zrot + env->angle[i[0]]) + env->p[0];
		p1[1] = p1[2] * sin(env->map->zrot + env->angle[i[0]]) + env->p[1];
		p1[2] = env->tall + env->p[2];
		k[2] = env->p[0] - p1[0];
		k[3] = env->p[1] - p1[1];
		if (fabs(k[2]) >= fabs(k[3]))
			ft_trace_x(i, p1, k, env);
		else
			ft_trace_y(i, p1, k, env);
		i[0]--;
	}
	pthread_exit(env->value[0]);
	return (env->value[0]);
}

void	*ft_raycasting1(void *arg)
{
	t_env	*env;
	int		i[7];
	double	p1[6];
	double	k[4];

	env = (t_env *)arg;
	i[5] = 1;
	i[6] = 1;
	i[0] = WIDTH_2 - 1;
	while (i[0] >= WIDTH_4)
	{
		p1[2] = (DEPTH / env->coef[i[0]]);
		p1[0] = p1[2] * cos(env->map->zrot + env->angle[i[0]]) + env->p[0];
		p1[1] = p1[2] * sin(env->map->zrot + env->angle[i[0]]) + env->p[1];
		p1[2] = env->tall + env->p[2];
		k[2] = env->p[0] - p1[0];
		k[3] = env->p[1] - p1[1];
		if (fabs(k[2]) >= fabs(k[3]))
			ft_trace_x(i, p1, k, env);
		else
			ft_trace_y(i, p1, k, env);
		i[0]--;
	}
	pthread_exit(env->value[1]);
	return (env->value[1]);
}

void	*ft_raycasting2(void *arg)
{
	t_env	*env;
	int		i[7];
	double	p1[6];
	double	k[4];

	env = (t_env *)arg;
	i[5] = 1;
	i[6] = 1;
	i[0] = WIDTH3_4 - 1;
	while (i[0] >= WIDTH_2)
	{
		p1[2] = (DEPTH / env->coef[i[0]]);
		p1[0] = p1[2] * cos(env->map->zrot + env->angle[i[0]]) + env->p[0];
		p1[1] = p1[2] * sin(env->map->zrot + env->angle[i[0]]) + env->p[1];
		p1[2] = env->tall + env->p[2];
		k[2] = env->p[0] - p1[0];
		k[3] = env->p[1] - p1[1];
		if (fabs(k[2]) >= fabs(k[3]))
			ft_trace_x(i, p1, k, env);
		else
			ft_trace_y(i, p1, k, env);
		i[0]--;
	}
	pthread_exit(env->value[2]);
	return (env->value[2]);
}

void	ft_raycasting3(t_env *env)
{
	int		i[7];
	double	p1[6];
	double	k[4];

	i[5] = 1;
	i[6] = 1;
	i[0] = WIDTH - 1;
	while (i[0] >= WIDTH3_4)
	{
		p1[2] = (DEPTH / env->coef[i[0]]);
		p1[0] = p1[2] * cos(env->map->zrot + env->angle[i[0]]) + env->p[0];
		p1[1] = p1[2] * sin(env->map->zrot + env->angle[i[0]]) + env->p[1];
		p1[2] = env->tall + env->p[2];
		k[2] = env->p[0] - p1[0];
		k[3] = env->p[1] - p1[1];
		if (fabs(k[2]) >= fabs(k[3]))
			ft_trace_x(i, p1, k, env);
		else
			ft_trace_y(i, p1, k, env);
		i[0]--;
	}
}

void	ft_make_thread(t_env *env)
{
	if (pthread_create(&env->thread[0], NULL, &ft_raycasting0, env))
		exit(ft_perror("pthread_create()", env));
	if (pthread_create(&env->thread[1], NULL, &ft_raycasting1, env))
		exit(ft_perror("pthread_create()", env));
	if (pthread_create(&env->thread[2], NULL, &ft_raycasting2, env))
		exit(ft_perror("pthread_create()", env));
}
