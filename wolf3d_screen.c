/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 14:01:48 by vlize             #+#    #+#             */
/*   Updated: 2015/09/30 14:01:49 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

void	*ft_fps(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
//	write(1, "fps : ", 6);
//	pthread_mutex_lock(&env->mutex[1]);
//	ft_putendn(env->fps);
//	env->fps = 0;
//	pthread_mutex_unlock(&env->mutex[1]);
	usleep(950000);
	return (arg);//ft_fps(env));
}

void	*ft_screen(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	usleep(13000);
	return (arg);
}
