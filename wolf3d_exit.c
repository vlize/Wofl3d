/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/12 16:17:02 by vlize             #+#    #+#             */
/*   Updated: 2015/06/12 16:17:03 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

void	ft_free_obj(t_obj *obj)
{
	t_obj	*tmp;

	if (!obj)
		return ;
	tmp = obj->next;
	ft_free(obj);
	return (ft_free_obj(tmp));
}

void	ft_free_pln(t_pln *pln)
{
	t_pln	*tmp;

	if (!pln)
		return ;
	tmp = pln->next;
	ft_free(pln);
	return (ft_free_pln(tmp));
}

void	ft_free_tab(t_block ***tab, size_t x, size_t y)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((i < x) && tab[i])
	{
		j = 0;
		while (j < y)
		{
			if (tab[i][j])
			{
				if (tab[i][j]->pln)
					ft_free_pln(tab[i][j]->pln);
				if (tab[i][j]->obj)
					ft_free_obj(tab[i][j]->obj);
				ft_free(tab[i][j]);
			}
			j++;
		}
		ft_free(tab[i]);
		i++;
	}
}

void	ft_free_map(t_map *map)
{
	if (map->fd > 2)
		close(map->fd);
	if (map->tab)
		ft_free_tab(map->tab, map->xblock, map->yblock);
	if (map->tex)
		ft_free(map->tex);
	if (map->color)
		ft_free(map->color);
	free(map);
}

int		ft_free_env(t_env *env)
{
	if (!env)
		return (0);
	if (env->mlx && env->load)
		mlx_destroy_image(env->mlx, env->load);
	if (env->mlx && env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->mlx && env->win)
		mlx_destroy_window(env->mlx, env->win);
	if (env->name)
		ft_free(env->name);
	if (env->key)
		ft_free(env->key);
	if (env->map)
		ft_free(env->map);
	if (env->fd > 2)
		close(env->fd);
	ft_free(env);
	return (0);
}
