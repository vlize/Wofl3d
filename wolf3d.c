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
	if (ft_put_data(map, line, &l, &(map->xpos0)) != 1)
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->ypos0)) != 1)
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->zpos0)) != 1)
		return (0);
	l++;
	if (ft_put_data(map, line, &l, &(map->zrot0)) != 1)
		return (0);
	map->zrot0 *= M_PI / 180;
	map->xpos = map->xpos0;
	map->ypos = map->ypos0;
	map->zpos = map->zpos0;
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
	map->xmin = 0 - ((BLOCK_SIZE * map->xblock) / 2);
	map->xmax = (BLOCK_SIZE * map->xblock) / 2;
	map->ymin = 0 - ((BLOCK_SIZE * map->yblock) / 2);
	map->ymax = (BLOCK_SIZE * map->xblock) / 2;
	return (ft_check_pos0(map, line, l));
}

static int	ft_make_env(t_env *env)
{
	env->rad_spd = ROT_SPD * RAD;
	env->hei = WIDTH * RESOLUTION;
	env->x = WIDTH / 2;
	env->y = env->hei / 2;
	env->depth = env->x / tan(SEMI_ANGLE);
	env->b = 4 * CHAR_BIT;
	env->l = 4 * WIDTH;
	env->en = ft_endian();
	env->gnl = get_next_line(env->fd, &(env->line));
	if (env->gnl == -1)
		return (ft_perror("get_next_line()", env));
	if (env->gnl == 0)
		return (ft_put_error("ft_make_env(): invalid map file.", env));
	if (!(env->map = (t_map *)malloc(sizeof(t_map))))
		return (ft_perror("malloc()", env));
	(env->map)->tab = NULL;
	if (!ft_check_map(env->map, env->line, 0, 0))
		return (ft_put_error("ft_make_env(): invalid map file.", env));
	if (!(env->mlx = mlx_init()))
		return (ft_perror("mlx_init()", env));
	if (!(env->win = mlx_new_window(env->mlx, WIDTH, env->hei, env->name)))
		return (ft_perror("mlx_new_window()", env));
	return (1);
}

static int	ft_check_arg(int ac, char **av, t_env *env)
{
	size_t	l;

	ft_init_env(env);
	if (ac < 2)
		return (ft_put_error("map name is missing.", env));
	else if (ac > 2)
		return (ft_put_error("too many arguments.", env));
	if ((env->fd = open(av[1], O_RDONLY)) == -1)
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
	char		*s;
	int			i[4];

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (ft_perror("malloc()", NULL));
	if (!ft_check_arg(ac, av, env) || !ft_make_env(env))
		return (0);
	if (!ft_make_tab(env->map, -1, -1) || !ft_init_loading(&s, i, env->hei))
		return (ft_perror("malloc()", env));
	if (!(env->load = mlx_xpm_file_to_image(env->mlx, s, &i[0], &i[1])))
		return (ft_perror("mlx_xpm_file_to_image()", env));
	mlx_put_image_to_window(env->mlx, env->win, env->load, i[2], i[3]);
	mlx_do_sync(env->mlx);
	if (ft_load_map(env, 0, &(env->map)->xtab, &(env->map)->ytab) == 0)
		return (0);
	if (!(env->img = mlx_new_image(env->mlx, WIDTH, env->hei)))
		return (ft_perror("mlx_new_image()", env));
	mlx_expose_hook(env->win, ft_expose_hook, env);
	mlx_hook(env->win, KeyPress, KeyPressMask, ft_keypress_hook, env);
	mlx_hook(env->win, KeyRelease, KeyReleaseMask, ft_keyrelease_hook, env);
	return (mlx_loop(env->mlx));
}
