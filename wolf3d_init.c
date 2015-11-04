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

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

void	ft_init_key(t_key *key)
{
	key->forth[0] = 0;
	key->forth[1] = 0;
	key->back[0] = 0;
	key->back[1] = 0;
	key->strafe_l = 0;
	key->strafe_r = 0;
	key->turn_l[0] = 0;
	key->turn_l[1] = 0;
	key->turn_r[0] = 0;
	key->turn_r[1] = 0;
	key->crouch = 0;
	key->jump = 0;
	key->use = 0;
}

void	ft_init_env(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->map = NULL;
	env->key = NULL;
	env->name = NULL;
	env->load = NULL;
	env->addr = NULL;
	env->line = NULL;
	env->fd = 0;
	env->rad_spd = ROT_SPD * RAD;
	env->bpp = 4 * CHAR_BIT;
	env->sl = 4 * WIDTH;
	env->endian = ft_endian();
	env->tall = TALL_MAX;
	env->spd = SPD_MAX;
}

int		ft_reset(t_env *env)
{
	env->p[0] = env->map->p0[0];
	env->p[1] = env->map->p0[1];
	env->p[2] = env->map->p0[2];
	env->map->zrot = env->map->zrot0;
	env->map->mspd = 0;
	env->key->forth[0] = 0;
	env->key->forth[1] = 0;
	env->key->back[0] = 0;
	env->key->back[1] = 0;
	env->map->sspd = 0;
	env->key->turn_l[0] = 0;
	env->key->turn_l[1] = 0;
	env->key->turn_r[0] = 0;
	env->key->turn_r[1] = 0;
	env->map->crch = 0;
	env->key->crouch = 0;
	env->map->jump = 0;
	env->key->jump = 0;
	env->map->fall = 0;
	env->key->use = 0;
	env->tall = TALL_MAX;
	env->spd = SPD_MAX;
	return (ft_expose_hook(env));
}

void	ft_init_map(t_map *map)
{
	map->fd = 0;
	map->tab = NULL;
	map->tex = NULL;
	map->color = NULL;
}

int		ft_init_win(t_env *env)
{
	int	i[4];

	ft_init_env(env);
	if (!(env->mlx = mlx_init()))
		return (ft_perror("mlx_init()", env));
	if (!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Wolf3D")))
		return (ft_perror("mlx_new_window()", env));
	i[0] = 240;
	i[1] = 24;
	i[2] = (WIDTH - i[0]) / 2;
	i[3] = (HEIGHT - i[1]) / 2;
	env->load = mlx_xpm_file_to_image(env->mlx, "loading.xpm", &i[0], &i[1]);
	if (!env->load)
		return (ft_perror("mlx_xpm_file_to_image()", env));
	mlx_put_image_to_window(env->mlx, env->win, env->load, i[2], i[3]);
	mlx_do_sync(env->mlx);
	return (1);
}
