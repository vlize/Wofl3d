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

#include "libft.h"
#include "wolf3d.h"
#include "wolf3d_color.h"

int		ft_ray_cast(int *i, double *p1, t_env *env)
{
	t_pln	*pln;
	double	*j;
	int		ret;

	ret = 0;
	pln = env->map->tab[i[1]][i[2]]->pln;
	while (pln)
	{
		if ((pln->type == 'W') || (pln->type == 'w'))
		{
			if ((j = ft_collision(env->p, p1, pln->p[0], pln->p[1])))
			{
				p1[0] = j[0];
				p1[1] = j[1];
				i[5] = pln->hex;
				ret = 1;
			}
		}
		else if ((pln->type == 'F') || (pln->type == 'f'))
			i[7] = pln->hex;
		else if ((pln->type == 'C') || (pln->type == 'c'))
			i[6] = pln->hex;
		pln = pln->next;
	}
	return (ret);
}

void	ft_cast_xp(int *i, double *p1, double *k, t_env *env)
{
	i[3]++;
	while (ft_limit_xy(i, env))
	{
		p1[2] = i[3] * BLOCK_SIZE;
		p1[3] = p1[2] * k[0] + k[1];
		i[4] = p1[3] / BLOCK_SIZE;
		if (ft_cast0_x(i, p1, k, env))
			return (ft_wall(i, &p1[4], env));
		i[2] = i[4];
		if ((i[2] < env->map->yblock) && (i[2] >= 0))
		{
			if (ft_ray_cast(i, &p1[2], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[2];
		p1[1] = p1[3];
		i[1] = i[3];
		i[3]++;
	}
	return (ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), AZURE, env));
}

void	ft_cast_xn(int *i, double *p1, double *k, t_env *env)
{
	while (ft_limit_xy(i, env))
	{
		p1[2] = i[1] * BLOCK_SIZE;
		p1[3] = p1[2] * k[0] + k[1];
		i[4] = p1[3] / BLOCK_SIZE;
		if (ft_cast0_x(i, p1, k, env))
			return (ft_wall(i, &p1[4], env));
		i[2] = i[4];
		if ((i[2] < env->map->yblock) && (i[2] >= 0))
		{
			if (ft_ray_cast(i, &p1[2], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[2];
		p1[1] = p1[3];
		i[3] = i[1];
		i[1]--;
	}
	return (ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), AZURE, env));
}

void	ft_cast_yp(int *i, double *p1, double *k, t_env *env)
{
	i[4]++;
	while (ft_limit_xy(i, env))
	{
		p1[3] = i[4] * BLOCK_SIZE;
		p1[2] = p1[3] * k[0] + k[1];
		i[3] = p1[2] / BLOCK_SIZE;
		if (ft_cast0_y(i, p1, k, env))
			return (ft_wall(i, &p1[4], env));
		i[1] = i[3];
		if ((i[1] < env->map->xblock) && (i[1] >= 0))
		{
			if (ft_ray_cast(i, &p1[2], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[2];
		p1[1] = p1[3];
		i[2] = i[4];
		i[4]++;
	}
	return (ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), DAWN, env));
}

void	ft_cast_yn(int *i, double *p1, double *k, t_env *env)
{
	while (ft_limit_xy(i, env))
	{
		p1[3] = i[2] * BLOCK_SIZE;
		p1[2] = p1[3] * k[0] + k[1];
		i[3] = p1[2] / BLOCK_SIZE;
		if (ft_cast0_y(i, p1, k, env))
			return (ft_wall(i, &p1[4], env));
		i[1] = i[3];
		if ((i[1] < env->map->xblock) && (i[1] >= 0))
		{
			if (ft_ray_cast(i, &p1[2], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[2];
		p1[1] = p1[3];
		i[4] = i[2];
		i[2]--;
	}
	return (ft_set_pixel(i[0], ((HEIGHT - 1) * WIDTH + i[0]), DAWN, env));
}
