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

void	ft_cast_xp(int *i, double *p1, double *k, t_env *env)
{
	i[3]++;
	while (ft_limit_xy(i, env))
	{
		p1[2] = i[3] * BLOCK_SIZE;
		p1[3] = p1[2] * k[0] + k[1];
		i[4] = p1[3] / BLOCK_SIZE;
		p1[4] = p1[2];
		p1[5] = p1[3];
		if ((i[2] != i[4]) && ft_cast0_x(i, p1, k, env))
			return (ft_wall(i, p1, env));
		if (((i[2] = i[4]) < env->map->yblock) && (i[2] >= 0))
		{
			if (ft_ray_cast(i, &p1[4], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[4];
		p1[1] = p1[5];
		i[1] = i[3];
		i[3]++;
	}
	return (ft_set_skybox(i[0], i[8], i[9], env));
}

void	ft_cast_xn(int *i, double *p1, double *k, t_env *env)
{
	while (ft_limit_xy(i, env))
	{
		p1[2] = i[1] * BLOCK_SIZE;
		p1[3] = p1[2] * k[0] + k[1];
		i[4] = p1[3] / BLOCK_SIZE;
		p1[4] = p1[2];
		p1[5] = p1[3];
		if ((i[2] != i[4]) && ft_cast0_x(i, p1, k, env))
			return (ft_wall(i, p1, env));
		if (((i[2] = i[4]) < env->map->yblock) && (i[2] >= 0))
		{
			if (ft_ray_cast(i, &p1[4], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[4];
		p1[1] = p1[5];
		i[3] = i[1];
		i[1]--;
	}
	return (ft_set_skybox(i[0], i[8], i[9], env));
}

void	ft_cast_yp(int *i, double *p1, double *k, t_env *env)
{
	i[4]++;
	while (ft_limit_xy(i, env))
	{
		p1[3] = i[4] * BLOCK_SIZE;
		p1[2] = p1[3] * k[0] + k[1];
		i[3] = p1[2] / BLOCK_SIZE;
		p1[4] = p1[2];
		p1[5] = p1[3];
		if ((i[1] != i[3]) && ft_cast0_y(i, p1, k, env))
			return (ft_wall(i, p1, env));
		if (((i[1] = i[3]) < env->map->xblock) && (i[1] >= 0))
		{
			if (ft_ray_cast(i, &p1[4], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[4];
		p1[1] = p1[5];
		i[2] = i[4];
		i[4]++;
	}
	return (ft_set_skybox(i[0], i[8], i[9], env));
}

void	ft_cast_yn(int *i, double *p1, double *k, t_env *env)
{
	while (ft_limit_xy(i, env))
	{
		p1[3] = i[2] * BLOCK_SIZE;
		p1[2] = p1[3] * k[0] + k[1];
		i[3] = p1[2] / BLOCK_SIZE;
		p1[4] = p1[2];
		p1[5] = p1[3];
		if ((i[1] != i[3]) && ft_cast0_y(i, p1, k, env))
			return (ft_wall(i, p1, env));
		if (((i[1] = i[3]) < env->map->xblock) && (i[1] >= 0))
		{
			if (ft_ray_cast(i, &p1[4], env))
				return (ft_wall(i, &p1[2], env));
			else
				ft_floor_ceiling(i, &p1[2], env);
		}
		p1[0] = p1[4];
		p1[1] = p1[5];
		i[4] = i[2];
		i[2]--;
	}
	return (ft_set_skybox(i[0], i[8], i[9], env));
}
