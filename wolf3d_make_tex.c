/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_make_tex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/09 11:35:46 by vlize             #+#    #+#             */
/*   Updated: 2015/11/09 11:35:50 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "wolf3d.h"

static void	ft_make_tex0(t_env *env)
{
	ft_load_texture("xpm/x_matter0.xpm", "x0", env);
	ft_load_texture("xpm/plaster0.xpm", "p0", env);
	ft_load_texture("xpm/plaster1.xpm", "p1", env);
	ft_load_texture("xpm/plaster2.xpm", "p2", env);
	ft_load_texture("xpm/plaster3.xpm", "p3", env);
	ft_load_texture("xpm/liquid0.xpm", "l0", env);
	ft_load_texture("xpm/grass0.xpm", "g0", env);
	ft_load_texture("xpm/grass1.xpm", "g1", env);
	ft_load_texture("xpm/grass1.xpm", "g2", env);
	ft_load_texture("xpm/rock0.xpm", "r0", env);
	ft_load_texture("xpm/rock1.xpm", "r1", env);
	ft_load_texture("xpm/rock2.xpm", "r2", env);
	ft_load_texture("xpm/sand0.xpm", "s0", env);
	ft_load_texture("xpm/sand1.xpm", "s1", env);
	ft_load_texture("xpm/sand2.xpm", "s2", env);
	ft_load_texture("xpm/wood0.xpm", "w0", env);
	ft_load_texture("xpm/wood1.xpm", "w1", env);
	ft_load_texture("xpm/wood2.xpm", "w2", env);
	ft_load_texture("xpm/tree0.xpm", "t0", env);
	ft_load_texture("xpm/tree1.xpm", "t1", env);
	ft_load_texture("xpm/tree2.xpm", "t2", env);
}

void		ft_make_tex(t_env *env)
{
	ft_load_texture("xpm/none.xpm", "99", env);
	ft_load_texture("xpm/brick0.xpm", "b0", env);
	ft_load_texture("xpm/brick1.xpm", "b1", env);
	ft_load_texture("xpm/brick2.xpm", "b2", env);
	ft_load_texture("xpm/brick3.xpm", "b3", env);
	ft_load_texture("xpm/brick4.xpm", "b4", env);
	ft_load_texture("xpm/floor0.xpm", "f0", env);
	ft_load_texture("xpm/floor1.xpm", "f1", env);
	ft_load_texture("xpm/floor2.xpm", "f2", env);
	ft_load_texture("xpm/floor3.xpm", "f3", env);
	ft_load_texture("xpm/floor4.xpm", "f4", env);
	ft_load_texture("xpm/floor5.xpm", "f5", env);
	ft_load_texture("xpm/floor6.xpm", "f6", env);
	ft_load_texture("xpm/floor7.xpm", "f7", env);
	ft_load_texture("xpm/metal0.xpm", "m0", env);
	ft_load_texture("xpm/metal1.xpm", "m1", env);
	ft_load_texture("xpm/metal2.xpm", "m2", env);
	ft_load_texture("xpm/metal3.xpm", "m3", env);
	ft_load_texture("xpm/metal4.xpm", "m4", env);
	ft_load_texture("xpm/metal5.xpm", "m5", env);
	ft_load_texture("xpm/metal6.xpm", "m6", env);
	ft_load_texture("xpm/metal7.xpm", "m7", env);
	ft_load_texture("xpm/metal8.xpm", "m8", env);
	ft_load_texture("xpm/metal9.xpm", "m9", env);
	return (ft_make_tex0(env));
}
