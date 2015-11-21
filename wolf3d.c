/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/12 15:46:50 by vlize             #+#    #+#             */
/*   Updated: 2015/06/12 15:46:52 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

static int	ft_check_pos0(t_map *map, char *line, size_t l)
{
	if (ft_put_data(map, line, &l, &(map->p0[0])) != 1)
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->p0[1])) != 1)
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->p0[2])) != 1)
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->zrot0)) != 1)
		return (0);
	ft_map_limits(map->p0, map);
	map->zrot0 *= RAD;
	map->zrot = map->zrot0;
	map->spd = SPD_MAX;
	map->mspd = 0;
	map->sspd = 0;
	map->jump = 0;
	map->fall = 0;
	map->crch = 0;
	return (1);
}

static int	ft_check_map(t_map *map, char *line, double data, size_t l)
{
	map->tab = NULL;
	map->tex = NULL;
	map->color = NULL;
	map->xtab = 0;
	map->ytab = 0;
	if (ft_put_data(map, line, &l, &data) != 1)
		return (0);
	map->xblock = (int)data;
	l++;
	if ((map->xblock < 1) || (ft_put_data(map, line, &l, &data) != 1))
		return (0);
	map->yblock = (int)data;
	l++;
	if ((map->yblock < 1) || (ft_put_data(map, line, &l, &(map->zmin)) != 1))
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->zmax)) != 1)
		return (0);
	l++;
	map->xmax = BLOCK_SIZE * map->xblock;
	map->ymax = BLOCK_SIZE * map->yblock;
	return (ft_check_pos0(map, line, l));
}

static int	ft_make_env(t_env *env)
{
	env->gnl = get_next_line(env->fd, &(env->line));
	if (env->gnl == -1)
		return (ft_perror("get_next_line()", env));
	if (env->gnl == 0)
		return (ft_put_error("ft_make_env(): invalid map file.", env));
	if (!(env->map = (t_map *)malloc(sizeof(t_map))))
		return (ft_perror("malloc()", env));
	if (!ft_check_map(env->map, env->line, 0, 0))
		return (ft_put_error("ft_make_env(): invalid map file.", env));
	if ((env->gnl = get_next_line(env->fd, &(env->line))) < 0)
		return (ft_perror("get_next_line()", env));
	if (env->gnl == 0)
		return (ft_put_error("get_next_line(): invalid map file.", env));
	if (!(env->map->tex = ft_strdup(env->line)))
		return (ft_perror("ft_strdup()", env));
	env->p[0] = env->map->p0[0];
	env->p[1] = env->map->p0[1];
	env->p[2] = env->map->p0[2];
	return (ft_make_coef(env));
}

static int	ft_check_arg(int ac, char **av, t_env *env)
{
	size_t	l;

	if (ac < 2)
		return (ft_put_error("map name is missing.", env));
	else if (ac > 2)
		return (ft_put_error("too many arguments.", env));
	env->name = av[1];
	if ((env->fd = open(av[1], O_RDONLY)) < 0)
		return (ft_perror("open()", env));
	l = ft_strlen(av[1]);
	while ((l != 0) && (av[1][l - 1] != '/'))
		l--;
	if (!(env->name = ft_strdup(&av[1][l])) || !ft_make_key(env))
		return (ft_perror("malloc()", env));
	return (1);
}

int			main(int ac, char **av)
{
	t_env		*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (ft_perror("malloc()", NULL));
	if (!ft_init_win(env) || !ft_check_arg(ac, av, env) || !ft_make_env(env))
		return (0);
	if (!ft_make_tab(env->map, -1, -1))
		return (ft_perror("malloc()", env));
	ft_make_tex(env);
	ft_load_map(env, 0, &(env->map)->xtab, &(env->map)->ytab);
	ft_load_skybox(env);
	if (!(env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		return (ft_perror("mlx_new_image()", env));
	env->addr = mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->endian);
	mlx_hook(env->win, KeyPress, KeyPressMask, ft_keypress_hook, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, ft_keyrelease_hook, env);
	mlx_loop_hook(env->mlx, ft_expose_hook, env);
	return (mlx_loop(env->mlx));
}
