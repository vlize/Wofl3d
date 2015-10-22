/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_cast.c                                      :+:      :+:    :+:   */
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

static int	ft_ray_cast(int *i, double *p1, t_env *env)
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
				i[6] = pln->hex;
				ret = 1;
			}
		}
		pln = pln->next;
	}
	return (ret);
}

static int	ft_limit_xy(int *i, t_env *env)
{
	if ((i[1] < 0) || (i[1] >= env->map->xblock))
		return (0);
	if ((i[2] < 0) || (i[2] >= env->map->yblock))
		return (0);
	return (1);
}

void		ft_cast_x(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[3] / k[2];
	k[1] = env->p[1] - (env->p[0] * k[0]);
	if (k[2] < 0)
		i[5] = -1;
	if (i[5] > 0)
		i[3]++;
	while (ft_limit_xy(i, env))
	{
		p1[3] = i[3] * BLOCK_SIZE;
		p1[4] = p1[3] * k[0] + k[1];
		i[4] = p1[4] / BLOCK_SIZE;
		if (ft_ray_cast(i, p1, env))
			return (ft_put_to_image(i, p1, env));
		if ((i[2] != i[4]) && ((i[2] = i[4]) < env->map->yblock) && (i[2] >= 0))
		{
			if (ft_ray_cast(i, p1, env))
				return (ft_put_to_image(i, p1, env));
		}
		i[1] = i[3];
		i[2] = i[4];
		i[3] += i[5];
	}
	return (ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), SKY0, env));
}

void		ft_cast_y(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[2] / k[3];
	k[1] = env->p[0] - (env->p[1] * k[0]);
	if (k[3] < 0)
		i[5] = -1;
	if (i[5] > 0)
		i[4]++;
	while (ft_limit_xy(i, env))
	{
		p1[4] = i[4] * BLOCK_SIZE;
		p1[3] = p1[4] * k[0] + k[1];
		i[3] = p1[3] / BLOCK_SIZE;
		if (ft_ray_cast(i, p1, env))
			return (ft_put_to_image(i, p1, env));
		if ((i[1] != i[3]) && ((i[1] = i[3]) < env->map->xblock) && (i[1] >= 0))
		{
			if (ft_ray_cast(i, p1, env))
				return (ft_put_to_image(i, p1, env));
		}
		i[1] = i[3];
		i[2] = i[4];
		i[4] += i[5];
	}
	return (ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), SKY1, env));
}
