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

static void	ft_key_event0(t_env *env)
{
	if (env->key->jump && !env->map->fall && (env->map->jump < JMP_MAX))
		env->map->jump += JMP_SPD;
	else if ((env->map->fall = 1))
		env->map->jump = 0;
	if (!k_c(env->key->forth) && !k_c(env->key->back) && (env->map->mspd < 0))
		env->map->mspd = 0;
	if (!k_c(env->key->back) && !k_c(env->key->forth) && (env->map->mspd > 0))
		env->map->mspd = 0;
	if (!env->key->strafe_l && !env->key->strafe_r && (env->map->sspd < 0))
		env->map->sspd = 0;
	if (!env->key->strafe_r && !env->key->strafe_l && (env->map->sspd > 0))
		env->map->sspd = 0;
}

void		ft_key_event(t_env *env)
{
	if (!env->key->crouch && (env->tall = TALL_MAX))
		env->spd = SPD_MAX;
	else if ((env->tall = TALL_MIN))
		env->spd = SPD_MIN;
	if (k_c(env->key->forth) && (!k_c(env->key->back) || (env->map->mspd < 0)))
		env->map->mspd = -1;
	if (k_c(env->key->back) && (!k_c(env->key->forth) || (env->map->mspd > 0)))
		env->map->mspd = 1;
	if (k_c(env->key->turn_l))
		env->map->zrot -= env->rad_spd;
	if (k_c(env->key->turn_r))
		env->map->zrot += env->rad_spd;
	ft_angle_limits(&(env->map->zrot));
	if (env->key->strafe_l && (!env->key->strafe_r || (env->map->sspd < 0)))
		env->map->sspd = -1;
	if (env->key->strafe_r && (!env->key->strafe_l || (env->map->sspd > 0)))
		env->map->sspd = 1;
	return (ft_key_event0(env));
}
