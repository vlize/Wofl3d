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
