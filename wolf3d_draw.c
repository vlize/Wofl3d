/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/28 15:54:19 by vlize             #+#    #+#             */
/*   Updated: 2015/09/28 15:54:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	ft_set_color(uint *n, int endian, char *s)
{
	if (endian == 1)
	{
		n[1] = (n[0] << 24) & 0xFF;
		n[2] = (n[0] << 16) & 0xFF;
		n[3] = (n[0] << 8) & 0xFF;
	}
	else
	{
		n[1] = n[0] & 0xFF;
		n[2] = (n[0] >> 8) & 0xFF;
		n[3] = (n[0] >> 16) & 0xFF;
	}
	ft_memcpy(s, &n[1], 1);
	ft_memcpy(&s[1], &n[2], 1);
	ft_memcpy(&s[2], &n[3], 1);
}

void	ft_set_texture(int *i, intmax_t *y, t_env *env)
{
	uint	n[4];
	int		j[3];
	double	k[2];

	if (y[0] >= y[1])
		return ;
	j[0] = (y[0] * WIDTH + i[0]) * 4;
	j[1] = (y[1] * WIDTH + i[0]) * 4;
	k[0] = (double)BLOCK_SIZE / y[3];
	k[1] = 0;
	if (y[2] < 0)
		k[1] = (0 - y[2]) * k[0];
	while (j[0] < j[1])
	{
		j[2] = k[1];
		if (j[2] >= BLOCK_SIZE)
			j[2] = BLOCK_SIZE - 1;
		n[0] = env->ret[0]->tex->tex[i[5]][j[2]];
		ft_set_color(n, env->endian, &env->addr[j[0]]);
		j[0] += INC_PIX;
		k[1] += k[0];
	}
}

void	ft_set_skybox(int x, int y, int ymax, t_env *env)
{
	uint	n[4];
	int		j[4];
	double	angle;

	if (y >= ymax)
		return ;
	j[0] = (y * WIDTH + x) * 4;
	j[1] = (ymax * WIDTH + x) * 4;
	j[2] = y;
	angle = env->angle0;
	ft_angle_limits(&angle);
	while (j[0] < j[1])
	{
		j[3] = angle * WIDTH4 / PI2;
		n[0] = env->map->sky[j[3]][j[2]];
		ft_set_color(n, env->endian, &env->addr[j[0]]);
		j[0] += INC_PIX;
		j[2]++;
	}
}

void	ft_set_pixel(int ymin, int ymax, int color, t_env *env)
{
	uint	n[4];
	int		j[2];

	if (ymin >= ymax)
		return ;
	n[0] = color;
	j[0] = ymin * 4;
	j[1] = ymax * 4;
	while (j[0] < j[1])
	{
		ft_set_color(n, env->endian, &env->addr[j[0]]);
		j[0] += INC_PIX;
	}
}
