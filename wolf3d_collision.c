/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/05 13:57:24 by vlize             #+#    #+#             */
/*   Updated: 2015/10/05 13:57:40 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static double	*ft_collision(double *a, double *b, double *c, double *d)
{
	static double	i[6];
	double			k[3];

	i[0] = a[0] - c[0];
	i[1] = a[1] - c[1];
	i[2] = b[0] - c[0];
	i[3] = b[1] - c[1];
	i[4] = d[0] - c[0];
	i[5] = d[1] - c[1];
	k[1] = (i[4] * i[1]) - (i[5] * i[0]);
	k[2] = (i[4] * i[3]) - (i[5] * i[2]);
	if (((k[1] > 0) && (k[2] > 0)) || ((k[1] < 0) && (k[2] < 0)))
		return (NULL);
	k[0] = ((a[0] - b[0]) * (c[1] - d[1])) - ((a[1] - b[1]) * (c[0] - d[0]));
	if (!k[0])
		return (NULL);
	k[1] = (a[0] * b[1]) - (a[1] * b[0]);
	k[2] = (c[0] * d[1]) - (c[1] * d[0]);
	i[0] = ((k[1] * (c[0] - d[0])) - (k[2] * (a[0] - b[0]))) / k[0];
	i[1] = ((k[1] * (c[1] - d[1])) - (k[2] * (a[1] - b[1]))) / k[0];
	if (((i[0] > c[0]) && (i[0] > d[0])) || ((i[0] < c[0]) && (i[0] < d[0])))
		return (NULL);
	if (((i[1] > c[1]) && (i[1] > d[1])) || ((i[1] < c[1]) && (i[1] < d[1])))
		return (NULL);
	return (i);
}

static void		ft_positon_check(t_pln *pln ,t_env *env)
{
	int		n[2];
	double	*i;

write(1, " ", 1);
	n[0] = 0;
	while (n[0] < pln->pts)
	{
		n[1] = n[0] + 1;
		if (n[1] == pln->pts)
			n[1] = 0;
		if ((i = ft_collision(env->p, env->map->p, pln->p[n[0]], pln->p[n[1]])))
		{
			i[2] = hypot(i[0] - env->p[0], i[1] - env->p[1]) - 1.5;
			env->map->p[0] = env->p[0] + (cos(env->mrot) * i[2]);
			env->map->p[1] = env->p[1] + (sin(env->mrot) * i[2]);
		}
		n[0]++;
	}
ft_putendn(n[0]);
}

static void		ft_block_check(int *i, t_env *env)
{
	i[0] = env->p[0] / BLOCK_SIZE;
	i[1] = env->map->p[0] / BLOCK_SIZE;
	i[2] = env->p[1] / BLOCK_SIZE;
	i[3] = env->map->p[1] / BLOCK_SIZE;
	if (i[0] < i[1])
	{
		i[4] = i[0];
		i[0] = i[1];
		i[1] = i[4];
	}
	if (i[2] < i[3])
	{
		i[4] = i[2];
		i[2] = i[3];
		i[3] = i[4];
	}
}

void			ft_crash_check(t_env *env)
{
	int		i[5];
	t_pln	*pln;

	ft_block_check(i, env);
	while (i[0] <= i[1])
	{
		i[4] = i[2];
		while (i[4] <= i[3])
		{
			pln = env->map->tab[i[0]][i[4]]->pln;
			while (pln)
			{
				if (pln->type == 'W')
					ft_positon_check(pln, env);
				pln = pln->next;
			}
			i[4]++;
		}
		i[0]++;
	}
	if ((env->map->p[2] < 0) && !(env->map->fall = 0))
		env->map->p[2] = 0;
	if ((env->map->p[2] >= BLOCK_SIZE) && (env->map->fall = 1))
		env->map->p[2] = BLOCK_SIZE;
write(1, "---\n", 4);
}
