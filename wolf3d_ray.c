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

int	ft_ray_cast(int *i, double *p1, t_env *env)
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
				i[5] = pln->hex;
				ret = 1;
			}
		}
		pln = pln->next;
	}
	return (ret);
}
