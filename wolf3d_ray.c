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
				i[5] = (j[0] * BLOCK_SIZE) / j[1];
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

	pln = env->map->tab[i[1]][i[2]]->pln;
	while (pln)
	{
		if ((pln->type == 'W') || (pln->type == 'w'))
		{
			if (ft_ray_cast0(i, p1, env, pln))
				env->ret[0] = pln;
		}
		else if ((pln->type == 'F') || (pln->type == 'f'))
		{
			env->ret[2] = pln;
			i[7] = pln->hex;
		}
		else if ((pln->type == 'C') || (pln->type == 'c'))
		{
			env->ret[1] = pln;
			i[6] = pln->hex;
		}
		pln = pln->next;
	}
	return (env->ret[0]);
}

static void	ft_init_equation(int *i, t_env *env)
{
	double	k[2];

	env->ret[0] = NULL;
	env->ret[1] = NULL;
	env->ret[2] = NULL;
	env->angle0 = env->map->zrot + env->angle[i[0]];
	env->cos0 = cos(env->angle0);
	env->sin0 = sin(env->angle0);
	env->coef0 = env->hypo[i[0]] / HEIGHT_2;
	env->pf[2] = env->p[2] + env->tall;
	env->pc[2] = BLOCK_SIZE - env->pf[2];
	k[0] = env->pf[2] * env->coef0;
	k[1] = env->pc[2] * env->coef0;
	env->pf[0] = env->p[0] + k[0] * env->cos0;
	env->pf[1] = env->p[1] + k[0] * env->sin0;
	env->pc[0] = env->p[0] + k[1] * env->cos0;
	env->pc[1] = env->p[1] + k[1] * env->sin0;
}

static void	ft_check_equation(int *i, double *p1, double *k, t_env *env)
{
	if (fabs(k[2]) >= fabs(k[3]))
	{
		k[0] = k[3] / k[2];
		k[1] = env->p[1] - (env->p[0] * k[0]);
		if (k[2] >= 0)
			return (ft_cast_xp(i, p1, k, env));
		else
			return (ft_cast_xn(i, p1, k, env));
	}
	k[0] = k[2] / k[3];
	k[1] = env->p[0] - (env->p[1] * k[0]);
	if (k[3] >= 0)
		return (ft_cast_yp(i, p1, k, env));
	else
		return (ft_cast_yn(i, p1, k, env));
}

void		ft_raycasting(t_env *env)
{
	double	p1[6];
	int		i[10];

	i[0] = -1;
	while ((i[0] += 1) < WIDTH)
	{
		i[6] = 0;
		i[7] = 0;
		i[8] = 0;
		i[9] = HEIGHT;
		i[1] = env->i[0];
		i[2] = env->i[1];
		i[3] = i[1];
		i[4] = i[2];
		ft_init_equation(i, env);
		p1[0] = env->p[0] + env->hypo[i[0]] * env->cos0;
		p1[1] = env->p[1] + env->hypo[i[0]] * env->sin0;
		env->k[2] = p1[0] - env->p[0];
		env->k[3] = p1[1] - env->p[1];
		p1[0] = env->p[0];
		p1[1] = env->p[1];
		ft_check_equation(i, p1, env->k, env);
	}
}
