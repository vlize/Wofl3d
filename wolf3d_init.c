/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/18 11:49:53 by vlize             #+#    #+#             */
/*   Updated: 2015/06/18 11:49:59 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		ft_init_key(t_env *env)
{
	if (!(env->key = (t_key *)malloc(sizeof(t_key))))
		return (0);
	env->key->forward = 0;
	env->key->backward = 0;
	env->key->strafe_l = 0;
	env->key->strafe_r = 0;
	env->key->turn_l = 0;
	env->key->turn_r = 0;
	env->key->crouch = 0;
	env->key->jump = 0;
	env->key->use = 0;
	return (1);
}

void	ft_init_loading(char **s, int *i, int height)
{
	*s = "loading.xpm";
	i[0] = 240;
	i[1] = 24;
	i[2] = (WIDTH - i[0]) / 2;
	i[3] = (height - i[1]) / 2;
}

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
