/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_load_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/19 09:24:49 by vlize             #+#    #+#             */
/*   Updated: 2015/06/19 09:24:50 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static int	ft_load_line(t_env *env, size_t *l, int x, int y)
{
	while (env->line[*l] != '\0')
	{
		if (ft_is_pln(env->line[*l]) == 1)
			ft_put_pln(env, l, ft_make_pln((env->map)->tab[x][y]));
		else if (ft_is_obj(env->line[*l]) == 1)
			ft_put_obj(env, l, ft_make_obj((env->map)->tab[x][y]));
		else if (env->line[*l] == '\t')
			(*l)++;
		else
			return (0);
	}
	return (1);
}

static void	ft_load_empty(size_t *l, int *x, int xblock)
{
	if ((*x + 1) < xblock)
		(*x)++;
	(*l)++;
}

void		ft_load_map(t_env *env, size_t l, int *x, int *y)
{
	env->gnl = get_next_line(env->fd, &(env->line));
	while (ft_check_gnl(env->fd, env, *y, env->map->yblock) > 0)
	{
		l = 0;
		if ((env->line[0] == '\0') && !(*x = 0))
			(*y)++;
		else if (env->line[0] == '#')
			ft_load_empty(&l, x, (env->map)->xblock);
		else if (ft_is_pln(env->line[l]) || ft_is_obj(env->line[l]))
		{
			if (ft_load_line(env, &l, *x, *y) == 0)
				exit(ft_put_error("ft_load_line(): invalid map file.", env));
			if ((*x + 1) < (env->map)->xblock)
				(*x)++;
		}
		else
			exit(ft_put_error("ft_load_map(): invalid map file.", env));
		env->gnl = get_next_line(env->fd, &(env->line));
	}
	if (env->gnl == -1)
		exit(ft_perror("get_next_line()", env));
	if ((env->fd = close(env->fd)))
		exit(ft_perror("close()", env));
}

void		ft_search_line(int fd, int *gnl, char **line)
{
	(*gnl) = get_next_line(fd, line);
	while (((*gnl) > 0) && ((*line)[0] != '"'))
		(*gnl) = get_next_line(fd, line);
}

t_color		*ft_load_color(int fd, int *n, t_env *env)
{
	t_color	*color;
	int		i[2];

	if (!(color = (t_color *)malloc(sizeof(t_color) * n[0])))
		return (ft_perror0("malloc()", env));
	ft_search_line(fd, &(env->gnl), &(env->line));
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
		env->gnl = get_next_line(fd, &(env->line));
	}
	return (color);
}
