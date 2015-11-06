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

int			ft_load_map(t_env *env, size_t l, int *x, int *y)
{
	while (ft_check_gnl(env, *y, env->map->yblock) > 0)
	{
		l = 0;
		if (env->line[0] == '\0')
		{
			*x = 0;
			(*y)++;
		}
		else if (env->line[0] == '#')
			ft_load_empty(&l, x, (env->map)->xblock);
		else if (ft_is_pln(env->line[l]) || ft_is_obj(env->line[l]))
		{
			if (ft_load_line(env, &l, *x, *y) == 0)
				return (ft_put_error("ft_load_line(): invalid map file.", env));
			if ((*x + 1) < (env->map)->xblock)
				(*x)++;
		}
		else
			return (ft_put_error("ft_load_map(): invalid map file.", env));
	}
	if (env->gnl == -1)
		return (ft_perror("get_next_line()", env));
	if ((env->fd = close(env->fd)))
		return (ft_perror("close()", env));
	return (1);
}

static int	ft_init_skybox(char *s, int *i, int *n)
{
	if (!ft_isdigit(s[*i]))
		return (0);
	(*n) = ft_atoi(&s[*i]);
	while (ft_isdigit(s[*i]))
		(*i) += 1;
	if ((s[*i] != ' ') && (s[*i] != '"'))
		return (0);
	(*i) += 1;
	return (1);
}

int			ft_load_skybox(t_env *env)
{
	int	i;

	i = 1;
	if ((env->fd = open(env->map->tex, O_RDONLY)) < 0)
		return (ft_perror("open()", env));
	ft_search_line(env->fd, &env->gnl, &(env->line));
	if (env->gnl < 0)
		return (ft_perror("get_next_line()", env));
	if ((env->gnl == 0) || !ft_isdigit(env->line[i]))
		return (ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_skybox(env->line, &i, &env->map->xsky))
		return (ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_skybox(env->line, &i, &env->map->ysky))
		return (ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_skybox(env->line, &i, env->map->csky))
		return (ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	if (!ft_init_skybox(env->line, &i, &env->map->csky[1]))
		return (ft_put_error("ft_load_skybox(): invalid XPM file.", env));
	return (ft_load_sky(env->map, env));
}
