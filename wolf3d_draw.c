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

static void	ft_collision(t_env *env)
{
	if (env->map->xpos > (WIDTH - 10))
		env->map->xpos = WIDTH - 10;
	else if (env->map->xpos < 0)
		env->map->xpos = 0;
	if (env->map->ypos > (env->hei - 20))
		env->map->ypos = env->hei - 20;
	else if (env->map->ypos < 5)
		env->map->ypos = 5;
	if (env->map->zpos < 0)
	{
		env->map->zpos = 0;
		env->map->fall = 0;
	}
	env->x = env->map->xpos;
	env->y = env->map->ypos;
}

void		ft_position(t_env *env)
{
	env->rot = env->map->zrot;
	env->map->spd = 0;
	if (env->map->mspd || env->map->sspd)
		env->map->spd = env->spd;
	if (env->map->mspd > 0)
		env->rot += PI_4 * env->map->sspd;
	else if (!env->map->mspd)
		env->rot += PI_2 * env->map->sspd;
	else
		env->rot += M_PI - (PI_4 * env->map->sspd);
	env->map->xpos += (cos(env->rot) * env->map->spd);
	env->map->ypos += (sin(env->rot) * env->map->spd);
	if (env->map->jump && !env->map->fall)
		env->map->zpos += JMP_SPD;
	else if (env->map->fall)
		env->map->zpos -= FALL_SPD;
	return (ft_collision(env));
}
