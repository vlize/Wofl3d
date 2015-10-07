/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/06 13:10:19 by vlize             #+#    #+#             */
/*   Updated: 2015/10/06 13:10:20 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

#define N 0.75

static void	ft_player(double x0, double y0, t_env *env)
{
	int	x[2];
	int	y[2];

	x[1] = x0 + 1;
	y[1] = y0 + 1;
	y[0] = y0 - 1;
	while (y[0] <= y[1])
	{
		x[0] = x0 - 1;
		while (x[0] <= x[1])
		{
			mlx_pixel_put(env->mlx, env->win, x[0] * N, y[0] * N, 0x00FF00);
			x[0]++;
		}
		y[0]++;
	}
}

static void	ft_trace_x(t_pln *b, double *k, int *i, t_env *env)
{
	double	x;
	double	y;

	x = b->p[i[0]][0];
	k[0] = k[3] / k[2];
	k[1] = b->p[i[0]][1] - (b->p[i[0]][0] * k[0]);
	if (k[2] > 0)
	{
		while (x <= b->p[i[1]][0])
		{
			y = x * k[0] + k[1];
			mlx_pixel_put(env->mlx, env->win, x * N, y * N, b->hex);
			x++;
		}
		return ;
	}
	while (x >= b->p[i[1]][0])
	{
		y = x * k[0] + k[1];
		mlx_pixel_put(env->mlx, env->win, x * N, y * N, b->hex);
		x--;
	}
}

static void	ft_trace_y(t_pln *b, double *k, int *i, t_env *env)
{
	double	x;
	double	y;

	y = b->p[i[0]][1];
	k[0] = k[2] / k[3];
	k[1] = b->p[i[0]][0] - (b->p[i[0]][1] * k[0]);
	if (k[3] > 0)
	{
		while (y <= b->p[i[1]][1])
		{
			x = y * k[0] + k[1];
			mlx_pixel_put(env->mlx, env->win, x * N, y * N, b->hex);
			y++;
		}
		return ;
	}
	while (y >= b->p[i[1]][1])
	{
		x = y * k[0] + k[1];
		mlx_pixel_put(env->mlx, env->win, x * N, y * N, b->hex);
		y--;
	}
}

static void	ft_border(t_pln *pln, t_env *e)
{
	int		i[4];
	double	k[4];

	i[0] = 0;
	while (i[0] < pln->pts)
	{
		i[1] = i[0] + 1;
		if (i[1] == pln->pts)
			i[1] = 0;
		k[2] = pln->p[i[1]][0] - pln->p[i[0]][0];
		k[3] = pln->p[i[1]][1] - pln->p[i[0]][1];
		if ((k[2] == 0) && (k[3] == 0))
		{
			i[2] = pln->p[i[0]][0];
			i[3] = pln->p[i[0]][1];
			mlx_pixel_put(e->mlx, e->win, i[2] * N, i[3] * N, pln->hex);
		}
		else if (fabs(k[2]) >= fabs(k[3]))
			ft_trace_x(pln, k, i, e);
		else
			ft_trace_y(pln, k, i, e);
		i[0]++;
	}
}

void		ft_aff_map(t_env *env)
{
	int		x;
	int		y;
	t_pln	*pln;

	x = 0;
	while (x <= env->map->xtab)
	{
		y = 0;
		while (y <= env->map->ytab)
		{
			pln = env->map->tab[x][y]->pln;
			while (pln)
			{
				if (pln->type == 'W')
					ft_border(pln, env);
				pln = pln->next;
			}
			y++;
		}
		x++;
	}
	ft_player(env->p[0], env->p[1], env);
}
