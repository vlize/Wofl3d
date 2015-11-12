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

static int	ft_ray_cast0(int *i, double *p1, t_env *env, t_pln *pln)
{
	double	*j;

	if ((j = ft_collision(env->p, p1, pln->p[0], pln->p[1])))
	{
		if ((pln->hex >= 0) || (pln->type == 'w'))
		{
			p1[0] = j[0];
			p1[1] = j[1];
			if (pln->type == 'w')
			{
				j[0] = hypot((pln->p[0][0] - p1[0]), (pln->p[0][1] - p1[1]));
				j[2] = pln->p[0][0] - pln->p[1][0];
				j[3] = pln->p[0][1] - pln->p[1][1];
				j[1] = hypot(j[2], j[3]);
				i[5] = (j[0] * BLOCK_SIZE / j[1]);
			}
			else
				i[5] = pln->hex;
			return (1);
		}
	}
	return (0);
}

t_pln		*ft_ray_cast(int *i, double *p1, t_env *env)
{
	t_pln	*pln;
	t_pln	*ret;

	ret = NULL;
	pln = env->map->tab[i[1]][i[2]]->pln;
	while (pln)
	{
		if ((pln->type == 'W') || (pln->type == 'w'))
		{
			if (ft_ray_cast0(i, p1, env, pln))
				ret = pln;
		}
		else if ((pln->type == 'F') || (pln->type == 'f'))
			i[7] = pln->hex;
		else if ((pln->type == 'C') || (pln->type == 'c'))
			i[6] = pln->hex;
		pln = pln->next;
	}
	return (ret);
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
		i[6] = 0;
		i[7] = 0;
		i[8] = 0;
		i[9] = HEIGHT;
		i[1] = env->i[0];
		i[2] = env->i[1];
		i[3] = i[1];
		i[4] = i[2];
		k[0] = env->map->zrot + env->angle[i[0]];
		p1[0] = env->p[0] + (env->hypo[i[0]] * cos(k[0]));
		p1[1] = env->p[1] + (env->hypo[i[0]] * sin(k[0]));
		k[2] = p1[0] - env->p[0];
		k[3] = p1[1] - env->p[1];
		ft_check_equation(i, p1, k, env);
		i[0]++;
	}
}
