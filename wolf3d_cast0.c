/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_cast0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/27 14:46:30 by vlize             #+#    #+#             */
/*   Updated: 2015/10/27 14:46:32 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		ft_cast0_x(int *i, double *p1, double *k, t_env *env)
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

int		ft_cast0_y(int *i, double *p1, double *k, t_env *env)
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
