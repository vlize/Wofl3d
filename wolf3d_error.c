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

int		ft_perror(char *error, t_env *env)
{
	ft_putstr_fd("\x1b[31mwolf3d: ", 2);
	perror(error);
	if (env)
		return (ft_free_env(env));
	return (0);
}

int		ft_put_error(char *error, t_env *env)
{
	ft_putstr_fd("\x1b[31mwolf3d: ", 2);
	ft_putendl_fd(error, 2);
	if (env)
		return (ft_free_env(env));
	return (0);
}

t_color	*ft_perror0(char *s, t_env *env)
{
	ft_perror(s, env);
	return (NULL);
}

t_color	*ft_put_error0(char *s, t_env *env)
{
	ft_put_error(s, env);
	return (NULL);
}

int		ft_check_border(double *i, double *c, double *d)
{
	if ((i[0] > c[0] + 0.0001) && (i[0] > d[0] + 0.0001))
		return (0);
	if ((i[0] < c[0] - 0.0001) && (i[0] < d[0] - 0.0001))
		return (0);
	if ((i[1] > c[1] + 0.0001) && (i[1] > d[1] + 0.0001))
		return (0);
	if ((i[1] < c[1] - 0.0001) && (i[1] < d[1] - 0.0001))
		return (0);
	return (1);
}
