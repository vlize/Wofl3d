/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/18 10:55:48 by vlize             #+#    #+#             */
/*   Updated: 2015/06/18 10:55:49 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

int		ft_is_op(int c)
{
	if ((c == '-') || (c == '+') || (c == '*') || (c == '/'))
		return (1);
	return (0);
}

int		ft_is_val(int c)
{
	if ((c == 'x') || (c == 'y') || (c == 'b'))
		return (1);
	else if ((c == 'X') || (c == 'Y'))
		return (1);
	return (0);
}

int		ft_is_pln(int c)
{
	if ((c == 'W') || (c == 'F') || (c == 'C'))
		return (1);
	else if ((c == 'w') || (c == 'f') || (c == 'c'))
		return (1);
	else if (ft_isdigit(c) == 1)
		return (1);
	return (0);
}

int		ft_is_obj(int c)
{
	if ((c == 'O') || (c == 'o'))
		return (1);
	return (0);
}

int		ft_check_gnl(t_env *env, int y)
{
	if (y >= env->map->yblock)
	{
		while (env->gnl)
			env->gnl = get_next_line(env->fd, &(env->line));
		return (0);
	}
	env->gnl = get_next_line(env->fd, &(env->line));
	return (env->gnl);
}
