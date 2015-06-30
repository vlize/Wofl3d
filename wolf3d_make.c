/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/30 16:22:34 by vlize             #+#    #+#             */
/*   Updated: 2015/06/30 16:22:42 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		ft_make_tab(t_map *map, int x, int y)
{
	if (!(map->tab = (t_block ***)malloc(sizeof(t_block) * map->xblock)))
		return (0);
	while ((x += 1) < map->xblock)
		map->tab[x] = NULL;
	x = -1;
	while ((x += 1) < map->xblock)
	{
		if (!(map->tab[x] = (t_block **)malloc(sizeof(t_block) * map->yblock)))
			return (0);
		while ((y += 1) < map->yblock)
			map->tab[x][y] = NULL;
		y = -1;
		while ((y += 1) < map->yblock)
		{
			if (!(map->tab[x][y] = (t_block *)malloc(sizeof(t_block))))
				return (0);
			(map->tab[x][y])->pln = NULL;
			(map->tab[x][y])->obj = NULL;
		}
	}
	return (1);
}

t_pln	*ft_make_pln(t_block *block)
{
	t_pln	*tmp;

	if (!(block->pln))
	{
		if (!(block->pln = (t_pln *)malloc(sizeof(t_pln))))
			return (NULL);
		(block->pln)->pts = 0;
		(block->pln)->next = NULL;
		return (block->pln);
	}
	tmp = block->pln;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_pln *)malloc(sizeof(t_pln))))
		return (NULL);
	(tmp->next)->pts = 0;
	(tmp->next)->next = NULL;
	return (tmp->next);
}

t_obj	*ft_make_obj(t_block *block)
{
	t_obj	*tmp;

	if (!(block->obj))
	{
		if (!(block->obj = (t_obj *)malloc(sizeof(t_obj))))
			return (NULL);
		(block->obj)->next = NULL;
		return (block->obj);
	}
	tmp = block->obj;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	(tmp->next)->next = NULL;
	return (tmp->next);
}
