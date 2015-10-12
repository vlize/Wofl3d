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

void	*ft_raycasting_lu(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->mutex[0]);
	pthread_mutex_unlock(&env->mutex[0]);
	pthread_exit(env->value[0]);
	return (env->value[0]);
}

void	*ft_raycasting_ru(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->mutex[1]);
	pthread_mutex_unlock(&env->mutex[1]);
	pthread_exit(env->value[1]);
	return (env->value[1]);
}

void	*ft_raycasting_ld(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	pthread_mutex_lock(&env->mutex[2]);
	pthread_mutex_unlock(&env->mutex[2]);
	pthread_exit(env->value[2]);
	return (env->value[2]);
}

void	ft_raycasting_rd(t_env *env)
{
	pthread_mutex_lock(&env->mutex[3]);
	pthread_mutex_unlock(&env->mutex[3]);
}
