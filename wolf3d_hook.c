/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/17 12:31:16 by vlize             #+#    #+#             */
/*   Updated: 2015/06/17 12:31:20 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

static void	aff_tab(t_map *map, int x, int y)
{
	t_pln	*tmp;
	int		i;

	while ((x += 1) < map->xblock)
	{
		ft_putchar('\n');
		y = 0;
		if (map->tab[x])
		{
			while (y < map->yblock)
			{
				ft_putnbr(x);
				ft_putchar('|');
				ft_putnbr(y);
				if (map->tab[x][y])
				{
					ft_putstr(" = ");
					tmp = (map->tab[x][y])->pln;
					while (tmp)
					{
						ft_putchar(tmp->type);
						ft_putchar(tmp->nbr);
						i = -1;
						while ((i += 1) < (tmp->pts))
						{
							ft_putchar('|');
							ft_putflt(tmp->p[i][0], 0);
							ft_putchar(';');
							ft_putflt(tmp->p[i][1], 0);
							ft_putchar(';');
							ft_putflt(tmp->p[i][2], 0);
						}
						tmp = tmp->next;
						if (tmp)
							ft_putstr(" -> ");
					}
				}
				ft_putchar('\n');
				y++;
			}
		}
	}
}

int			ft_expose_hook(t_env *env)
{
	if (env->map && (env->map)->tab)
		aff_tab(env->map, -1, 0);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_string_put(env->mlx, env->win, 640, 400, 65280, "\\(^_^)/");
	mlx_do_sync(env->mlx);
	return (0);
}

int			ft_key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(ft_free_env(env));
	else
		return (0);
	return (mlx_expose_hook(env->mlx, ft_expose_hook, env));
}
