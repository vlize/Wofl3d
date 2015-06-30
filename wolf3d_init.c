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

#include "libft.h"
#include "wolf3d.h"

static void	ft_init_key2(t_key *key)
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

int			ft_init_key(t_env *env)
{
	if (!(env->key = (t_key *)malloc(sizeof(t_key))))
		return (0);
	if (!(env->key0 = (t_key *)malloc(sizeof(t_key))))
		return (0);
	ft_init_key2(env->key);
	ft_init_key2(env->key0);
	return (1);
}

void		ft_init_loading(char **s, int *i, int height)
{
	*s = "loading.xpm";
	i[0] = 240;
	i[1] = 24;
	i[2] = (WIDTH - i[0]) / 2;
	i[3] = (height - i[1]) / 2;
}
