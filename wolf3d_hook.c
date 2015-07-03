/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/17 12:31:16 by vlize             #+#    #+#             */
/*   Updated: 2015/06/17 12:31:20 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

static void	ft_position(int *pos, int lim, int spd)
{
	(*pos) += spd;
	if ((*pos) < 0)
		(*pos) += lim;
	else if ((*pos) >= lim)
		(*pos) -= lim;
}

int			ft_expose_hook(t_env *env)
{
	int		i;
	char	*s;

	ft_position(&(env->x), WIDTH, env->map->sspd);
	ft_position(&(env->y), env->hei, env->map->mspd);
	i = env->y - 10 + (env->key->crouch * 10);
	s = ft_itoa(env->map->zrot);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_string_put(env->mlx, env->win, env->x, env->y, env->color, s);
	mlx_string_put(env->mlx, env->win, env->x, i, env->color, s);
	mlx_string_put(env->mlx, env->win, env->x, env->y, 0xFFFFFF, "_");
	mlx_do_sync(env->mlx);
	usleep(5);
	return (0);
}

int			ft_keyrelease_hook(int keycode, t_env *env)
{
	if (keycode == 13)
		env->key->forth[0] = 0;
	if (keycode == 1)
		env->key->back[0] = 0;
	if (keycode == 12)
		env->key->turn_l[0] = 0;
	if (keycode == 14)
		env->key->turn_r[0] = 0;
	if (keycode == 0)
		env->key->strafe_l = 0;
	if (keycode == 2)
		env->key->strafe_r = 0;
	if (keycode == 36)
		env->key->use = 0;
	if (keycode == 8)
		env->key->crouch = 0;
	if (keycode == 126)
		env->key->forth[1] = 0;
	if (keycode == 125)
		env->key->back[1] = 0;
	if (keycode == 123)
		env->key->turn_l[1] = 0;
	if (keycode == 124)
		env->key->turn_r[1] = 0;
	return (ft_key_event(env));
}

static int	ft_keypress_hook0(int keycode, t_env *env)
{
	if (keycode == 126)
		env->key->forth[1] = 1;
	if (keycode == 125)
		env->key->back[1] = 1;
	if (keycode == 123)
		env->key->turn_l[1] = 1;
	if (keycode == 124)
		env->key->turn_r[1] = 1;
	return (ft_key_event(env));
}

int			ft_keypress_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(ft_free_env(env));
	if (keycode == 13)
		env->key->forth[0] = 1;
	if (keycode == 1)
		env->key->back[0] = 1;
	if (keycode == 12)
		env->key->turn_l[0] = 1;
	if (keycode == 14)
		env->key->turn_r[0] = 1;
	if (keycode == 0)
		env->key->strafe_l = 1;
	if (keycode == 2)
		env->key->strafe_r = 1;
	if (keycode == 36)
		env->key->use = 1;
	if (keycode == 8)
		env->key->crouch = 1;
	if ((keycode == 49) && !env->map->fall && (env->map->jump < SPD_MAX))
		env->key->jump = 1;
	return (ft_keypress_hook0(keycode, env));
}
