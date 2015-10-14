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
				p1[3] = i[0];
				p1[4] = i[1];
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
	while ((i[1] >= 0) && (i[1] < env->map->xblock))
	{
		p1[3] = i[3] * BLOCK_SIZE;
		p1[4] = p1[3] * k[0] + k[1];
		p1[5] = p1[2];
		i[4] = p1[4] / BLOCK_SIZE;
		while (i[2] != (i[4] + i[6]))
		{
			if (ft_ray_check(i, p1, env))
				return ;
			i[2] += i[6];
		}
		i[1] = i[3];
		i[3] += i[5];
	}
}

void		ft_trace_y(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[2] / k[3];
	k[1] = p1[0] - (p1[1] * k[0]);
	ft_init_ray(i, k, env);
	i[4] = i[2];
	if (i[6] > 0)
		i[4]++;
	while ((i[2] >= 0) && (i[2] < env->map->yblock))
	{
		p1[4] = i[2] * BLOCK_SIZE;
		p1[3] = p1[4] * k[0] + k[1];
		p1[5] = p1[2];
		i[3] = p1[3] / BLOCK_SIZE;
		while (i[1] != (i[3] + i[5]))
		{
			if (ft_ray_check(i, p1, env))
				return ;
			i[1] += i[5];
		}
		i[2] = i[4];
		i[4] += i[5];
	}
}
