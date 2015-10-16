/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/15 13:10:21 by vlize             #+#    #+#             */
/*   Updated: 2015/06/15 13:10:21 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		ft_put_error(char *error, t_env *env)
{
	ft_putstr_fd("\x1b[31mwolf3d: ", 2);
	ft_putendl_fd(error, 2);
	return (ft_free_env(env));
}

int		ft_perror(char *error, t_env *env)
{
	ft_putstr_fd("\x1b[31mwolf3d: ", 2);
	perror(error);
	return (ft_free_env(env));
}

void	ft_map_limits(double *p, t_map *map)
{
	if (p[0] < 0)
		p[0] = 0;
	else if (p[0] >= map->xmax)
		p[0] = map->xmax - 1;
	if (p[1] < 0)
		p[1] = 0;
	else if (p[1] >= map->ymax)
		p[1] = map->ymax - 1;
}

void	ft_window_limits(int *y, int *ymax)
{
	if ((*y) < 0)
		(*y) = 0;
	if ((*ymax) >= HEIGHT)
		(*ymax) = HEIGHT - 1;
}

void	ft_make_thread(t_env *env)
{
	if (pthread_create(&env->thread[0], NULL, &ft_raycasting0, env))
		exit(ft_perror("pthread_create()", env));
	if (pthread_create(&env->thread[1], NULL, &ft_raycasting1, env))
		exit(ft_perror("pthread_create()", env));
	if (pthread_create(&env->thread[2], NULL, &ft_raycasting2, env))
		exit(ft_perror("pthread_create()", env));
}
