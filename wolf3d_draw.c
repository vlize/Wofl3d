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

static void	ft_set_color(uint *n, int color, int endian)
{
	n[0] = color;
	if (endian == 1)
	{
		n[1] = (n[0] << 24) & 0xFF;
		n[2] = (n[0] << 16) & 0xFF;
		n[3] = (n[0] << 8) & 0xFF;
	}
	else
	{
		n[1] = n[0] & 0xFF;
		n[2] = (n[0] >> 8) & 0xFF;
		n[3] = (n[0] >> 16) & 0xFF;
	}
}

void		ft_set_pixel(int ymin, int ymax, int color, t_env *env)
{
	uint	n[4];
	int		j[2];

	if (ymin >= ymax)
		return ;
	ft_set_color(n, color, env->endian);
	j[0] = ymin * 4;
	j[1] = ymax * 4;
	while (j[0] < j[1])
	{
		ft_memcpy((env->addr + j[0]), &n[1], 1);
		ft_memcpy((env->addr + j[0] + 1), &n[2], 1);
		ft_memcpy((env->addr + j[0] + 2), &n[3], 1);
		j[0] += INC_PIX;
	}
}

static void	ft_check_equation(int *i, double *p1, double *k, t_env *env)
{
	p1[0] = env->p[0];
	p1[1] = env->p[1];
	if (fabs(k[2]) >= fabs(k[3]))
	{
		k[0] = k[3] / k[2];
		k[1] = env->p[1] - (env->p[0] * k[0]);
		if (k[2] >= 0)
			ft_cast_xp(i, p1, k, env);
		else
			ft_cast_xn(i, p1, k, env);
	}
	else
	{
		k[0] = k[2] / k[3];
		k[1] = env->p[0] - (env->p[1] * k[0]);
		if (k[3] >= 0)
			ft_cast_yp(i, p1, k, env);
		else
			ft_cast_yn(i, p1, k, env);
	}
}

void		ft_raycasting(t_env *env)
{
	double	p1[6];
	double	k[4];
	int		i[10];

	i[0] = 0;
	while (i[0] < WIDTH)
	{
		i[6] = F5;
		i[7] = F5;
		i[8] = 0;
		i[9] = HEIGHT;
		i[1] = env->i[0];
		i[2] = env->i[1];
		i[3] = i[1];
		i[4] = i[2];
		k[0] = env->map->zrot + env->angle[i[0]];
		p1[0] = env->p[0] + (env->hypo[i[0]] * cos(k[0]));
		p1[1] = env->p[1] + (env->hypo[i[0]] * sin(k[0]));
		p1[2] = env->tall + env->p[2];
		k[2] = p1[0] - env->p[0];
		k[3] = p1[1] - env->p[1];
		ft_check_equation(i, p1, k, env);
		i[0]++;
	}
}
