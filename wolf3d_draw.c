/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/28 15:54:19 by vlize             #+#    #+#             */
/*   Updated: 2015/09/28 15:54:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void		ft_position(t_env *env)
{
	env->mrot = env->map->zrot;
	env->map->spd = 0;
	if (env->map->mspd || env->map->sspd)
		env->map->spd = env->spd;
	if (env->map->mspd > 0)
		env->mrot += PI_4 * env->map->sspd;
	else if (!env->map->mspd)
		env->mrot += PI_2 * env->map->sspd;
	else
		env->mrot += M_PI - (PI_4 * env->map->sspd);
	env->map->p[0] = env->p[0] + (cos(env->mrot) * env->map->spd);
	env->map->p[1] = env->p[1] + (sin(env->mrot) * env->map->spd);
	if (env->map->jump && !env->map->fall)
		env->map->p[2] = env->p[2] + JMP_SPD;
	else if (env->map->fall)
		env->map->p[2] = env->p[2] - FALL_SPD;
	ft_crash_check(env);
	env->p[0] = env->map->p[0];
	env->p[1] = env->map->p[1];
	env->p[2] = env->map->p[2];
}
