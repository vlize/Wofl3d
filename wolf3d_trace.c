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
	i[1] = env->i[0];
	i[2] = env->i[1];
}

void	ft_trace_y(int *i, double *p1, double *k, t_env *env)
{
	k[0] = k[2] / k[3];
	k[1] = p1[0] - (p1[1] * k[0]);
	i[1] = env->i[0];
	i[2] = env->i[1];
}
