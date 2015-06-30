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

#include "libft.h"
#include "wolf3d.h"

static int	k_c(int *key)
{
	if (key[0] || key[1])
		return (1);
	return (0);
}

static int	ft_key_event3(t_env *env)
{
	if ((env->map->jump < env->spd) && env->key->jump)
		env->map->jump += 5;
	else
		env->map->jump = 0;
	if (!env->key->forth[0] && !env->key->forth[1] && (env->map->mspd < 0))
		env->map->mspd = 0;
	if (!env->key->back[0] && !env->key->back[1] && (env->map->mspd > 0))
		env->map->mspd = 0;
	if (!env->key->strafe_l && (env->map->sspd < 0))
		env->map->sspd = 0;
	if (!env->key->strafe_r && (env->map->sspd > 0))
		env->map->sspd = 0;
	return (ft_expose_hook(env));
}

static int	ft_key_event2(t_env *env)
{
	while (env->map->zrot >= 360)
		env->map->zrot -= 360;
	while (env->map->zrot < 0)
		env->map->zrot += 360;
	if (env->key->strafe_l && (!env->key->strafe_r || (env->map->sspd < 0)))
	{
		if (env->map->sspd > -env->spd)
			env->map->sspd -= 5;
		if (env->map->sspd < -env->spd)
			env->map->sspd = -env->spd;
	}
	if (env->key->strafe_r && (!env->key->strafe_l || (env->map->sspd > 0)))
	{
		if (env->map->sspd < env->spd)
			env->map->sspd += 5;
		if (env->map->sspd > env->spd)
			env->map->sspd = env->spd;
	}
	if (env->key->use)
		env->color = 0xFF0000;
	else
		env->color = 0xFF00;
	return (ft_key_event3(env));
}

int			ft_key_event(t_env *env)
{
	if (!env->key->crouch)
		env->spd = SPD_MAX;
	else
		env->spd = SPD_MAX / 3;
	if (k_c(env->key->forth) && (!k_c(env->key->back) || (env->map->mspd < 0)))
	{
		if (env->map->mspd > -env->spd)
			env->map->mspd -= 5;
		if (env->map->mspd < -env->spd)
			env->map->mspd = -env->spd;
	}
	if (k_c(env->key->back) && (!k_c(env->key->forth) || (env->map->mspd > 0)))
	{
		if (env->map->mspd < env->spd)
			env->map->mspd += 5;
		if (env->map->mspd > env->spd)
			env->map->mspd = env->spd;
	}
	if (env->key->turn_l[0] || env->key->turn_l[1])
		env->map->zrot += 5;
	if (env->key->turn_r[0] || env->key->turn_r[1])
		env->map->zrot -= 5;
	return (ft_key_event2(env));
}
