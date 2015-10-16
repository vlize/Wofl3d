/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/06 11:13:41 by vlize             #+#    #+#             */
/*   Updated: 2015/10/06 11:13:42 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"
#include "wolf3d_color.h"

static uint	ft_wall_color(int i)
{
	if (i == 0)
		return (W0);
	if (i == 1)
		return (W1);
	if (i == 2)
		return (W2);
	if (i == 3)
		return (W3);
	if (i == 4)
		return (W4);
	if (i == 5)
		return (W5);
	if (i == 6)
		return (W6);
	if (i == 7)
		return (W7);
	if (i == 8)
		return (W8);
	if (i == 9)
		return (W9);
	return (0xff0000);
}

static uint	ft_floor_color(int i)
{
	if (i == 0)
		return (F0);
	if (i == 1)
		return (F1);
	if (i == 2)
		return (F2);
	if (i == 3)
		return (F3);
	if (i == 4)
		return (F4);
	if (i == 5)
		return (F5);
	if (i == 6)
		return (F6);
	if (i == 7)
		return (F7);
	if (i == 8)
		return (F8);
	if (i == 9)
		return (F9);
	return (0xff0000);
}

uint		ft_put_color(char c, int i)
{
	if ((c == 'W') || (c == 'w'))
		return (ft_wall_color(i));
	if ((c == 'F') || (c == 'f') || (c == 'C') || (c == 'c'))
		return (ft_floor_color(i));
	if ((c == 'O') || (c == 'o'))
		return (0x0000ff);
	return (0xff0000);
}

static void	ft_set_color(uint *n, int color, int endian)
{
	n[0] = color;
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
}

void		ft_set_pixel(int pix, int pixmax, int color, t_env *env)
{
	uint	n[4];

	ft_set_color(n, color, env->endian);
	pix *= 4;
	pixmax *= 4;
	while (pix <= pixmax)
	{
		ft_memcpy((env->addr + pix), &n[1], 1);
		ft_memcpy((env->addr + pix + 1), &n[2], 1);
		ft_memcpy((env->addr + pix + 2), &n[3], 1);
		pix += INC_PIX;
	}
}
