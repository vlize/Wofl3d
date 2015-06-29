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

static void	ft_key_event3(t_env *env)
{
	if ((env->map->jump < 20) && env->key->jump)
		env->map->jump += 5;
	else
		env->map->jump = 0;
	if (!(env->key->forward) && (env->map->mspd < 0))
		env->map->mspd = 0;
	if (!(env->key->backward) && (env->map->mspd > 0))
		env->map->mspd = 0;
	if (!(env->key->strafe_l) && (env->map->sspd < 0))
		env->map->sspd = 0;
	if (!(env->key->strafe_r) && (env->map->sspd > 0))
		env->map->sspd = 0;
}

static void	ft_key_event2(t_env *env)
{
	if (env->key->strafe_l && (!env->key->strafe_r || (env->map->sspd < 0)))
	{
		if (env->map->sspd > 0)
			env->map->sspd = -5;
		if (env->map->sspd > -20)
			env->map->sspd -= 5;
	}
	if (env->key->strafe_r && (!env->key->strafe_l || (env->map->sspd > 0)))
	{
		if (env->map->sspd < 0)
			env->map->sspd = 5;
		if (env->map->sspd < 20)
			env->map->sspd += 5;
	}
	if (env->key->use)
	{
		env->color += 5;
		if (env->color > 0xFF)
			env->color += 0x500;
		if (env->color > 0xFFFF)
			env->color += 0x50000;
		if (env->color > 0xFFFFFF)
			env->color = 0;
	}
	return (ft_key_event3(env));
}

void		ft_key_event(t_env *env)
{
	if (env->key->forward && (!env->key->backward || (env->map->mspd < 0)))
	{
		if (env->map->mspd > 0)
			env->map->mspd = -5;
		if (env->map->mspd > -20)
			env->map->mspd -= 5;
	}
	if (env->key->backward && (!env->key->forward || (env->map->mspd > 0)))
	{
		if (env->map->mspd < 0)
			env->map->mspd = 5;
		if (env->map->mspd < 20)
			env->map->mspd += 5;
	}
	if (env->key->turn_l)
		env->map->zrot += 5;
	if (env->key->turn_r)
		env->map->zrot -= 5;
	while (env->map->zrot >= 360)
		env->map->zrot -= 360;
	while (env->map->zrot < 0)
		env->map->zrot += 360;
	return (ft_key_event2(env));
}
