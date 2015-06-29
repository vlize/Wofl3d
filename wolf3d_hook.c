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

int			ft_expose_hook(t_env *env)
{
	int	i[2];

	i[0] = (WIDTH / 2) + ((env->map)->sspd * 10);
	i[1] = (env->hei / 2) + ((env->map)->mspd * 10);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_string_put(env->mlx, env->win, i[0], i[1], env->color, ft_itoa());
	mlx_do_sync(env->mlx);
	return (0);
}

int			ft_keyrelease_hook(int keycode, t_env *env)
{
	if ((keycode == 126) || (keycode == 13))
		env->key->forward = 0;
	if ((keycode == 125) || (keycode == 1))
		env->key->backward = 0;
	if ((keycode == 123) || (keycode == 12))
		env->key->turn_l = 0;
	if ((keycode == 124) || (keycode == 14))
		env->key->turn_r = 0;
	if (keycode == 0)
		env->key->strafe_l = 0;
	if (keycode == 2)
		env->key->strafe_r = 0;
	if ((keycode == 36) || (keycode == 76))
		env->key->use = 0;
	ft_key_event(env);
	return (ft_expose_hook(env));
}

int			ft_keypress_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(ft_free_env(env));
	if ((keycode == 126) || (keycode == 13))
		env->key->forward = 1;
	if ((keycode == 125) || (keycode == 1))
		env->key->backward = 1;
	if ((keycode == 123) || (keycode == 12))
		env->key->turn_l = 1;
	if ((keycode == 124) || (keycode == 14))
		env->key->turn_r = 1;
	if (keycode == 0)
		env->key->strafe_l = 1;
	if (keycode == 2)
		env->key->strafe_r = 1;
	if ((keycode == 36) || (keycode == 76))
		env->key->use = 1;
	if ((keycode == 49) && !env->map->fall && (env->map->jump < 20))
		env->key->jump = 1;
	ft_key_event(env);
	return (ft_expose_hook(env));
}
