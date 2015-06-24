/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/23 15:36:19 by vlize             #+#    #+#             */
/*   Updated: 2015/06/23 15:36:20 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

int			ft_keyrelease_hook(int keycode, t_env *env)
{
	if (ft_check_key(keycode) != 1)
		return (0);
	if (((keycode == 126) || (keycode == 13)) && ((env->map)->mspd > 0))
		(env->map)->mspd = 0;
	if (((keycode == 125) || (keycode == 1)) && ((env->map)->mspd < 0))
		(env->map)->mspd = 0;
	if ((keycode == 0) && ((env->map)->sspd > 0))
		(env->map)->sspd = 0;
	if ((keycode == 2) && ((env->map)->sspd < 0))
		(env->map)->sspd = 0;
	return (mlx_loop_hook(env->mlx, ft_expose_hook, env));
}

static int	ft_keypress_hook2(int keycode, t_env *env)
{
	if (keycode == 0)
	{
		if ((env->map)->sspd < 0)
			(env->map)->sspd = 5;
		if ((env->map)->sspd < 20)
			(env->map)->sspd += 5;
	}
	else if (keycode == 2)
	{
		if ((env->map)->sspd > 0)
			(env->map)->sspd = -5;
		if ((env->map)->sspd > -20)
			(env->map)->sspd -= 5;
	}
	return (ft_key_hook(keycode, env));
}

int			ft_keypress_hook(int keycode, t_env *env)
{
	if (ft_check_key(keycode) == 0)
		return (ft_key_hook(keycode, env));
	if ((keycode == 126) || (keycode == 13))
	{
		if ((env->map)->mspd < 0)
			(env->map)->mspd = 5;
		if ((env->map)->mspd < 20)
			(env->map)->mspd += 5;
	}
	else if ((keycode == 125) || (keycode == 1))
	{
		if ((env->map)->mspd > 0)
			(env->map)->mspd = -5;
		if ((env->map)->mspd > -20)
			(env->map)->mspd -= 5;
	}
	if ((keycode == 123) || (keycode == 12))
		(env->map)->zrot += 5;
	else if ((keycode == 124) || (keycode == 14))
		(env->map)->zrot -= 5;
	while ((env->map)->zrot >= 360)
		(env->map)->zrot -= 360;
	while ((env->map)->zrot < 0)
		(env->map)->zrot += 360;
	return (ft_keypress_hook2(keycode, env));
}
