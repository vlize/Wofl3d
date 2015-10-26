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
#include "wolf3d_color.h"

void	ft_wall(int *i, double *p1, t_env *env)
{
	int		y[2];
	double	k[2];

	k[0] = hypot((env->p[0] - p1[0]), (env->p[1] - p1[1])) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	ft_window_limits(&y[0], &y[1]);
	ft_set_pixel((y[0] * WIDTH + i[0]), (y[1] * WIDTH + i[0]), i[5], env);
	y[0]--;
	y[1]++;
	ft_window_limits(&y[1], &y[0]);
	ft_set_pixel((y[1] * WIDTH + i[0]), (i[9] * WIDTH + i[0]), i[7], env);
	ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
}

void	ft_floor_ceiling(int *i, double *p1, t_env *env)
{
	int		y[2];
	double	k[2];

	k[0] = hypot((env->p[0] - p1[0]), (env->p[1] - p1[1])) * env->coef[i[0]];
	k[1] = ((env->p[2] + env->tall) * DEPTH) / k[0];
	y[0] = HEIGHT_2 + k[1] - (DEPTH * BLOCK_SIZE / k[0]);
	y[1] = HEIGHT_2 + k[1];
	ft_window_limits(&y[0], &y[1]);
	y[0]--;
	y[1]++;
	ft_window_limits(&y[1], &y[0]);
	ft_set_pixel((y[1] * WIDTH + i[0]), (i[9] * WIDTH + i[0]), i[7], env);
	ft_set_pixel((i[8] * WIDTH + i[0]), (y[0] * WIDTH + i[0]), i[6], env);
	i[9] = y[1] - 1;
	i[8] = y[0] + 1;
}

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
