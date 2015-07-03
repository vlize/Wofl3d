/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_loading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/16 10:14:34 by vlize             #+#    #+#             */
/*   Updated: 2015/06/16 10:14:35 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void	ft_set_color(unsigned int *n, t_env *e)
{
	if (endian() == 1)
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
	ft_memcpy(e->d, &n[1], 1);
	ft_memcpy(e->d + 1, &n[2], 1);
	ft_memcpy(e->d + 2, &n[3], 1);
}

void	ft_loading(t_env *env)
{
	char	*s;
	int		x;
	int		y;
	uint	n[4];

	n[0] = 0;
	s = "LOADING";
	env->addr = mlx_get_data_addr(env->img, &(env->b), &(env->l), &(env->en));
}

void	*ft_expose_hook(void *ptr)
{
	int		i;
	char	*s;
	t_env	*env;

	env = (t_env *)ptr;
	while (env->thread == 1)
		return (ft_expose_hook(ptr));
	env->thread = 2;
	ft_position(&(env->x), WIDTH, env->map->sspd);
	ft_position(&(env->y), env->hei, env->map->mspd);
	i = env->y - 10 + (env->key->crouch * 10);
	s = ft_itoa(env->map->zrot);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_string_put(env->mlx, env->win, env->x, env->y, env->color, s);
	mlx_string_put(env->mlx, env->win, env->x, i, env->color, s);
	mlx_string_put(env->mlx, env->win, env->x, env->y, 0xFFFFFF, "_");
	ft_putendl("sync_start");
	mlx_do_sync(env->mlx);
	ft_putendl("sync_end");
	env->thread = 0;
	usleep(10);
	return (ft_expose_hook(ptr));
}
