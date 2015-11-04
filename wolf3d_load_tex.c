/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_load_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/03 14:48:08 by vlize             #+#    #+#             */
/*   Updated: 2015/11/03 14:48:09 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

void			ft_search_line(int fd, int *gnl, char **line)
{
	(*gnl) = get_next_line(fd, line);
	while (((*gnl) > 0) && ((*line)[0] != '"'))
		(*gnl) = get_next_line(fd, line);
}

static t_color	*ft_load_color(int *n, t_env *env)
{
	t_color	*color;
	int		i[2];

	if (!(color = (t_color *)malloc(sizeof(t_color) * n[0])))
		return (ft_perror0("malloc()", env));
	ft_search_line(env->map->fd, &(env->gnl), &(env->line));
	i[0] = -1;
	while ((i[0] += 1) < n[0])
	{
		if (env->gnl < 0)
			return (ft_perror0("get_next_line()", env));
		if ((env->gnl == 0) || (env->line[0] != '"'))
			return (ft_put_error0("ft_load_color(): invalid XPM file.", env));
		i[1] = -1;
		while ((i[1] += 1) < n[1])
			color[i[0]].c[i[1]] = env->line[i[1] + 1];
		if (ft_strncmp(&(env->line[i[1] + 1]), " c #", 4))
			return (ft_put_error0("ft_load_color(): invalid XPM file.", env));
		color[i[0]].hex = ft_xtoi(&(env->line[i[1] + 5]));
		env->gnl = get_next_line(env->map->fd, &(env->line));
	}
	return (color);
}

static int		ft_put_tex(int *i, char *line, t_map *map)
{
	int		j[3];

	if (line[0] != '"')
		return (0);
	j[0] = i[0] * map->csky[1] + 1;
	j[1] = -1;
	while ((j[1] += 1) < map->csky[0])
	{
		j[2] = -1;
		while ((j[2] += 1) < map->csky[1])
		{
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

int				ft_load_tex(t_map *map, t_env *env)
{
	int		i[2];

	if (!(map->color = ft_load_color(map->csky, env)))
		return (0);
	ft_search_line(map->fd, &(env->gnl), &(env->line));
	i[1] = -1;
	while ((i[1] += 1) < HEIGHT)
	{
		if (env->gnl < 0)
			return (ft_perror("get_next_line()", env));
		if ((env->gnl == 0) || (env->line[0] != '"'))
			return (ft_put_error("ft_load_tex(): invalid XPM file.", env));
		i[0] = -1;
		while ((i[0] += 1) < WIDTH4)
		{
			if (!ft_put_tex(i, env->line, map))
				return (ft_put_error("ft_put_tex(): invalid XPM file.", env));
		}
		env->gnl = get_next_line(map->fd, &(env->line));
	}
	return (1);
}
