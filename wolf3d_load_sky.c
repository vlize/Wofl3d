/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_load_sky.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 14:48:08 by vlize             #+#    #+#             */
/*   Updated: 2015/11/03 14:48:09 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static int	ft_put_sky(int *i, char *line, t_map *map)
{
	int		j[3];

	j[0] = i[0] * map->csky[1] + 1;
	j[1] = -1;
	while ((j[1] += 1) < map->csky[0])
	{
		j[2] = -1;
		while ((j[2] += 1) < map->csky[1])
		{
			if ((line[j[0] + j[2]] == '\0') && !(map->sky[i[0]][i[1]] = 0))
				break ;
			if (line[j[0] + j[2]] != map->color[j[1]].c[j[2]])
				break ;
		}
		if (j[2] == map->csky[1])
		{
			map->sky[i[0]][i[1]] = map->color[j[1]].hex;
			return (1);
		}
	}
	return (0);
}

static void	ft_load_sky(t_map *map, t_env *env)
{
	int		i[2];

	if (!(map->color = ft_load_color(map->csky, env)))
		exit(0);
	ft_search_line(env->fd, &(env->gnl), &(env->line));
	i[1] = -1;
	while (ft_check_gnl(env->fd, env, (i[1] += 1), HEIGHT) > 0)
	{
		if (env->line[0] != '"')
			exit(ft_put_error("ft_load_sky(): invalid XPM file.", env));
		i[0] = -1;
		while ((i[0] += 1) < WIDTH4)
		{
			if (!ft_put_sky(i, env->line, map))
				exit(ft_put_error("ft_put_sky(): invalid XPM file.", env));
		}
		env->gnl = get_next_line(env->fd, &(env->line));
	}
	if (env->gnl < 0)
		exit(ft_perror("get_next_line()", env));
	if ((env->fd = close(env->fd)))
		exit(ft_perror("close()", env));
}

void		ft_load_skybox(t_env *env)
{
	int	i;

	if ((env->fd = open(env->map->tex, O_RDONLY)) < 0)
		exit(ft_perror("open()", env));
	ft_search_line(env->fd, &env->gnl, &(env->line));
	if (env->gnl < 0)
		exit(ft_perror("get_next_line()", env));
	i = 1;
	if ((env->gnl == 0) || !ft_isdigit(env->line[i]))
		exit(ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, &env->map->xsky))
		exit(ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, &env->map->ysky))
		exit(ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, env->map->csky))
		exit(ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, &env->map->csky[1]))
		exit(ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	return(ft_load_sky(env->map, env));
}
