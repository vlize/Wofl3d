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
		if (pln->hex >= 0)
		{
			p1[0] = j[0];
			p1[1] = j[1];
			i[5] = pln->hex;
			return (1);
		}
	}
	return (0);
}

int			ft_ray_cast(int *i, double *p1, t_env *env)
{
	t_pln	*pln;
	int		ret;

	ret = 0;
	pln = env->map->tab[i[1]][i[2]]->pln;
	while (pln)
	{
		if ((pln->type == 'W') || (pln->type == 'w'))
		{
			if (ft_ray_cast0(i, p1, env, pln))
				ret = 1;
		}
		else if ((pln->type == 'F') || (pln->type == 'f'))
			i[7] = pln->hex;
		else if ((pln->type == 'C') || (pln->type == 'c'))
			i[6] = pln->hex;
		pln = pln->next;
	}
	return (ret);
}

int			ft_cast0_x(int *i, double *p1, double *k, t_env *env)
{
	if (i[2] > i[4])
		p1[5] = i[2] * BLOCK_SIZE;
	else
		p1[5] = i[4] * BLOCK_SIZE;
	p1[4] = (p1[5] - k[1]) / k[0];
	if (ft_ray_cast(i, &p1[4], env))
		return (1);
	else
		ft_floor_ceiling(i, &p1[4], env);
	return (0);
}

int			ft_cast0_y(int *i, double *p1, double *k, t_env *env)
{
	if (i[1] > i[3])
		p1[4] = i[1] * BLOCK_SIZE;
	else
		p1[4] = i[3] * BLOCK_SIZE;
	p1[5] = (p1[4] - k[1]) / k[0];
	if (ft_ray_cast(i, &p1[4], env))
		return (1);
	else
		ft_floor_ceiling(i, &p1[4], env);
	return (0);
}
