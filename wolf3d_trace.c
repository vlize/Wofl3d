/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 15:48:22 by vlize             #+#    #+#             */
/*   Updated: 2015/10/12 15:48:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"
#include "wolf3d_color.h"

static void	ft_put_to_image(int *i, double *p1, t_env *env)
{
	int		y[3];
	double	k[2];

	k[0] = hypot((env->p[0] - p1[3]), (env->p[1] - p1[4])) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	ft_window_limits(&y[0], &y[1]);
	ft_set_pixel((y[0] * WIDTH + i[0]), (y[1] * WIDTH + i[0]), i[9], env);
	y[0]--;
	y[1]++;
	y[2] = HEIGHT - 1;
	ft_window_limits(&y[1], &y[0]);
	ft_set_pixel((y[1] * WIDTH + i[0]), (y[2] * WIDTH + i[0]), i[8], env);
	ft_set_pixel(i[0], (y[0] * WIDTH + i[0]), i[7], env);
}

static int	ft_ray_check(int *i, double *p1, t_env *env)
{
	t_pln	*pln;
	double	*j;
	int		ret;

	ret = 0;
	pln = env->map->tab[i[1]][i[2]]->pln;
	while (pln)
	{
		if (pln->type == 'W')
		{
			if ((j = ft_collision(env->p, &p1[3], pln->p[0], pln->p[1])))
			{
				p1[3] = j[0];
				p1[4] = j[1];
				i[9] = pln->hex;
				ret = 1;
			}
		}
		pln = pln->next;
	}
	return (ret);
}

static void	ft_init_ray(int *i, double *k, t_env *env)
{
	if (k[2] < 0)
		i[5] = -1;
	if (k[3] < 0)
		i[6] = -1;
	i[1] = env->i[0];
	i[2] = env->i[1];
}

void		ft_trace_x(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[3] / k[2];
	k[1] = p1[1] - (p1[0] * k[0]);
	ft_init_ray(i, k, env);
	i[3] = i[1];
	if (i[5] > 0)
		i[3]++;
	while ((i[3] >= 0) && (i[3] <= env->map->xblock))
	{
		p1[3] = i[3] * BLOCK_SIZE;
		p1[4] = p1[3] * k[0] + k[1];
		if ((p1[4] < 0) || (p1[4] > env->map->ymax))
			break ;
		i[4] = p1[4] / BLOCK_SIZE;
		if (ft_ray_check(i, p1, env))
			return (ft_put_to_image(i, p1, env));
		if (i[2] != i[4])
		{
			i[2] = i[4];
			if (ft_ray_check(i, p1, env))
				return (ft_put_to_image(i, p1, env));
		}
		i[1] = i[3];
		i[3] += i[5];
	}
	ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), SKY0, env);
}

void		ft_trace_y(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[2] / k[3];
	k[1] = p1[0] - (p1[1] * k[0]);
	ft_init_ray(i, k, env);
	i[4] = i[2];
	if (i[6] > 0)
		i[4]++;
	while ((i[4] >= 0) && (i[4] <= env->map->yblock))
	{
		p1[4] = i[4] * BLOCK_SIZE;
		p1[3] = p1[4] * k[0] + k[1];
		if ((p1[3] < 0) || (p1[3] > env->map->xmax))
			break ;
		i[3] = p1[3] / BLOCK_SIZE;
		if (ft_ray_check(i, p1, env))
			return (ft_put_to_image(i, p1, env));
		if (i[1] != i[3])
		{
			i[1] = i[3];
			if (ft_ray_check(i, p1, env))
				return (ft_put_to_image(i, p1, env));
		}
		i[2] = i[4];
		i[4] += i[5];
	}
	ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), SKY0, env);
}
