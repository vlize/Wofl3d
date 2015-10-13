/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 15:48:22 by vlize             #+#    #+#             */
/*   Updated: 2015/10/12 15:48:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

void	ft_trace_x(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[3] / k[2];
	k[1] = p1[1] - (p1[0] * k[0]);
	if (k[2] < 0)
		i[5] = -1;
	if (k[3] < 0)
		i[6] = -1;
	i[1] = env->i[0];
	i[2] = env->i[1];
	i[3] = i[1];
	if (i[5] > 0)
		i[3]++;
	p1[3] = i[3] * BLOCK_SIZE;
	p1[4] = p1[3] * k[0] + k[1];
	p1[5] = p1[2];
	i[4] = p1[4] / BLOCK_SIZE;
}

void	ft_trace_y(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[2] / k[3];
	k[1] = p1[0] - (p1[1] * k[0]);
	if (k[2] < 0)
		i[6] = -1;
	if (k[3] < 0)
		i[5] = -1;
	i[1] = env->i[1];
	i[2] = env->i[0];
	i[3] = i[3];
	if (i[5] > 0)
		i[3]++;
	p1[4] = i[3] * BLOCK_SIZE;
	p1[3] = p1[4] * k[0] + k[1];
	p1[5] = p1[2];
	i[4] = p1[3] / BLOCK_SIZE;
}
