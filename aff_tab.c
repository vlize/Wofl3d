/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 15:36:19 by vlize             #+#    #+#             */
/*   Updated: 2015/06/23 15:36:20 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static void	aff_tab_block(t_pln *tmp)
{
	int		i;

	while (tmp)
	{
		ft_putchar(tmp->type);
		ft_putchar(tmp->color);
		ft_putnbr(tmp->nbr);
		ft_putchar('|');
		ft_putstr(ft_itox(tmp->hex, 1));
		i = -1;
		while ((i += 1) < (tmp->pts))
		{
			ft_putchar('|');
			ft_putflt(tmp->p[i][0], 0);
			ft_putchar(';');
			ft_putflt(tmp->p[i][1], 0);
			ft_putchar(';');
			ft_putflt(tmp->p[i][2], 0);
		}
		tmp = tmp->next;
		if (tmp)
			ft_putstr(" -> ");
	}
}

void		aff_tab(t_map *map, int x, int y)
{
	t_pln	*tmp;

	while ((x += 1) < map->xblock)
	{
		ft_putchar('\n');
		y = 0;
		if (map->tab[x])
		{
			while (y < map->yblock)
			{
				ft_putnbr(x);
				ft_putchar('|');
				ft_putnbr(y);
				if (map->tab[x][y])
				{
					ft_putstr(" = ");
					tmp = map->tab[x][y]->pln;
					aff_tab_block(tmp);
				}
				ft_putchar('\n');
				y++;
			}
		}
	}
}
