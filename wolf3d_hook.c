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

int			ft_check_key(int key)
{
	if ((key == 126) || (key == 13) || (key == 125) || (key == 1))
		return (1);
	else if ((key == 0) || (key == 2))
		return (1);
	else if ((key == 123) || (key == 14) || (key == 124) || (key == 14))
		return (2);
	return (0);
}

int			ft_expose_hook(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_string_put(env->mlx, env->win, 640, 400, 65280, "\\(^_^)/");
	mlx_do_sync(env->mlx);
	return (0);
}

int			ft_key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(ft_free_env(env));
	else if ((keycode == 36) || (keycode == 76))
	{
		ft_putstr("\x1b[33mUse key = ");
		ft_putendn(keycode);
	}
	else
		return (0);
	return (mlx_expose_hook(env->mlx, ft_expose_hook, env));
}
