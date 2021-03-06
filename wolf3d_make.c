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

int		ft_make_coef(t_env *env)
{
	int	i;

	env->hypo[WIDTH_2] = DEPTH;
	env->coef[WIDTH_2] = 1;
	env->angle[WIDTH_2] = 0;
	i = 1;
	while (i <= WIDTH_2)
	{
		env->hypo[WIDTH_2 - i] = sqrt(pow(DEPTH, 2) + (i * i));
		env->coef[WIDTH_2 - i] = DEPTH / env->hypo[WIDTH_2 - i];
		env->angle[WIDTH_2 - i] = 0 - atan2(i, DEPTH);
		i++;
	}
	while (i < WIDTH)
	{
		env->hypo[i] = env->hypo[WIDTH - i];
		env->coef[i] = env->coef[WIDTH - i];
		env->angle[i] = 0 - env->angle[WIDTH - i];
		i++;
	}
	return (1);
}

int		ft_make_key(t_env *env)
{
	if (!(env->key = (t_key *)malloc(sizeof(t_key))))
		return (0);
	ft_init_key(env->key);
	return (1);
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
		(block->pln)->tex = NULL;
		(block->pln)->next = NULL;
		return (block->pln);
	}
	tmp = block->pln;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_pln *)malloc(sizeof(t_pln))))
		return (NULL);
	(tmp->next)->pts = 0;
	(tmp->next)->tex = NULL;
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
