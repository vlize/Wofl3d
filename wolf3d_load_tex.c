/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_load_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/09 14:09:33 by vlize             #+#    #+#             */
/*   Updated: 2015/11/09 14:09:35 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

static int	ft_init_tmp(char *s2, t_tex **tmp)
{
	while (*tmp)
		tmp = &(*tmp)->next;
	if (!(*tmp = (t_tex *)malloc(sizeof(t_tex))))
		return (0);
	(*tmp)->type = s2[0];
	(*tmp)->nbr = s2[1] - 48;
	(*tmp)->color = NULL;
	(*tmp)->next = NULL;
	return (1);
}

static int	ft_put_tex(int *i, char *line, t_tex *tmp)
{
	int		j[3];

	j[0] = i[0] * tmp->ctex[1] + 1;
	j[1] = -1;
	while ((j[1] += 1) < tmp->ctex[0])
	{
		j[2] = -1;
		while ((j[2] += 1) < tmp->ctex[1])
		{
			if ((line[j[0] + j[2]] == '\0') && !(tmp->tex[i[0]][i[1]] = 0))
				break ;
			if (line[j[0] + j[2]] != tmp->color[j[1]].c[j[2]])
				break ;
		}
		if (j[2] == tmp->ctex[1])
		{
			tmp->tex[i[0]][i[1]] = tmp->color[j[1]].hex;
			return (1);
		}
	}
	return (0);
}

static void	ft_load_tex(t_tex *tmp, t_env *env)
{
	int		i[2];

	if (!(tmp->color = ft_load_color(tmp->ctex, env)))
		exit(0);
	ft_search_line(env->fd2, &(env->gnl), &(env->line));
	i[1] = -1;
	while (ft_check_gnl(env->fd2, env, (i[1] += 1), BLOCK_SIZE) > 0)
	{
		if (env->line[0] != '"')
			exit(ft_put_error("ft_load_tex(): invalid XPM file.", env));
		i[0] = -1;
		while ((i[0] += 1) < BLOCK_SIZE)
		{
			if (!ft_put_tex(i, env->line, tmp))
				exit(ft_put_error("ft_put_tex(): invalid XPM file.", env));
		}
		env->gnl = get_next_line(env->fd2, &(env->line));
	}
	if (env->gnl < 0)
		exit(ft_perror("get_next_line()", env));
	if ((env->fd2 = close(env->fd2)))
		exit(ft_perror("close()", env));
}

void		ft_load_texture(char *s1, char *s2, t_env *env)
{
	int		i;
	t_tex	**tmp;

	tmp = &env->tex;
	if (!(ft_init_tmp(s2, tmp)))
		exit(ft_perror("malloc()", env));
	if ((env->fd2 = open(s1, O_RDONLY)) < 0)
		exit(ft_perror("open()", env));
	ft_search_line(env->fd2, &env->gnl, &(env->line));
	if (env->gnl < 0)
		exit(ft_perror("get_next_line()", env));
	i = 1;
	if ((env->gnl == 0) || !ft_isdigit(env->line[i]))
		exit(ft_put_error("ft_load_texture(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, &(*tmp)->xtex))
		exit(ft_put_error("ft_load_texture(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, &(*tmp)->ytex))
		exit(ft_put_error("ft_load_texture(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, (*tmp)->ctex))
		exit(ft_put_error("ft_load_texture(): invalid XPM file.", env));
	if (!ft_init_xpm(env->line, &i, &(*tmp)->ctex[1]))
		exit(ft_put_error("ft_load_texture(): invalid XPM file.", env));
	return (ft_load_tex(*tmp, env));
}
