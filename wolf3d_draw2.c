/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_draw2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/28 15:54:19 by vlize             #+#    #+#             */
/*   Updated: 2015/09/28 15:54:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static void	ft_tex_limits(int *x, int *y)
{
	if (*x >= BLOCK_SIZE)
		*x = BLOCK_SIZE - 1;
	else if (*x < 0)
		*x = 0;
	if (*y >= BLOCK_SIZE)
		*y = BLOCK_SIZE - 1;
	else if (*y < 0)
		*y = 0;
}

static void	ft_set_tex_fc(double *tmp, double *p, int *j, int *i)
{
	j[2] = i[1] * BLOCK_SIZE;
	j[3] = i[2] * BLOCK_SIZE;
	p[0] = tmp[0];
	p[1] = tmp[1];
	j[5] = p[0] - j[2];
	j[6] = p[1] - j[3];
	ft_tex_limits(&j[5], &j[6]);
}

static void	ft_set_tex_coef(double *p, int *j, double k, t_env *env)
{
	j[4]--;
	p[2] = k / j[4];
	p[0] = env->p[0] + p[2] * env->cos0;
	p[1] = env->p[1] + p[2] * env->sin0;
	j[5] = p[0] - j[2];
	j[6] = p[1] - j[3];
	ft_tex_limits(&j[5], &j[6]);
}

void		ft_set_tex_f(int *i, intmax_t *y, double *p1, t_env *env)
{
	int		j[7];
	uint	n[4];
	double	p[3];

	if (y[1] >= i[9])
		return ;
	j[0] = ((y[1] - 1) * WIDTH + i[0]) * 4;
	j[1] = ((i[9] - 1) * WIDTH + i[0]) * 4;
	j[4] = i[9] - HEIGHT_2;
	ft_set_tex_fc(ft_ray_limits(p1, env->pf, env->p), p, j, i);
	while (j[1] > j[0])
	{
		n[0] = env->ret[2]->tex->tex[j[5]][j[6]];
		ft_set_color(n, env->endian, &env->addr[j[1]]);
		ft_set_tex_coef(p, j, (env->pf[2] * env->hypo[i[0]]), env);
		j[1] -= INC_PIX;
	}
}

void		ft_set_tex_c(int *i, intmax_t *y, double *p1, t_env *env)
{
	int		j[7];
	uint	n[4];
	double	p[3];

	if (i[8] >= y[0])
		return ;
	j[0] = (i[8] * WIDTH + i[0]) * 4;
	j[1] = (y[0] * WIDTH + i[0]) * 4;
	j[4] = HEIGHT_2 - i[8];
	ft_set_tex_fc(ft_ray_limits(p1, env->pc, env->p), p, j, i);
	while (j[0] < j[1])
	{
		n[0] = env->ret[1]->tex->tex[j[5]][j[6]];
		ft_set_color(n, env->endian, &env->addr[j[0]]);
		ft_set_tex_coef(p, j, (env->pc[2] * env->hypo[i[0]]), env);
		j[0] += INC_PIX;
	}
}
