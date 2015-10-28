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

static uint	ft_color_0(int i)
{
	if (i == 0)
		return (WHITE);
	else if (i == 1)
		return (GREY0);
	else if (i == 2)
		return (GREY1);
	else if (i == 3)
		return (GREY2);
	else if (i == 4)
		return (GREY3);
	else if (i == 5)
		return (GREY4);
	else if (i == 6)
		return (BLACK);
	else if (i == 7)
		return (MAROON0);
	else if (i == 8)
		return (MAROON1);
	return (MAROON2);
}

static uint	ft_color_1(int i)
{
	if (i == 0)
		return (ORANGE0);
	else if (i == 1)
		return (ORANGE1);
	else if (i == 2)
		return (ORANGE2);
	else if (i == 3)
		return (RED0);
	else if (i == 4)
		return (RED1);
	else if (i == 5)
		return (RED2);
	else if (i == 6)
		return (VIOLET0);
	else if (i == 7)
		return (VIOLET1);
	else if (i == 8)
		return (VIOLET2);
	return (MAGENTA);
}

static uint	ft_color_2(int i)
{
	if (i == 0)
		return (YELLOW0);
	else if (i == 1)
		return (YELLOW1);
	else if (i == 2)
		return (YELLOW2);
	else if (i == 3)
		return (GREEN0);
	else if (i == 4)
		return (GREEN1);
	else if (i == 5)
		return (GREEN2);
	else if (i == 6)
		return (BLUE0);
	else if (i == 7)
		return (BLUE1);
	else if (i == 8)
		return (BLUE2);
	return (CYAN);
}

uint		ft_put_color(char c, int i)
{
	if (c == '0')
		return (ft_color_0(i));
	else if (c == '1')
		return (ft_color_1(i));
	else if (c == '2')
		return (ft_color_2(i));
	else if ((c == 'O') || (c == 'o'))
		return (BEIGE);
	return (NIGHT);
}
