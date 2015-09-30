/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 14:47:37 by vlize             #+#    #+#             */
/*   Updated: 2015/06/11 14:48:43 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>

# define WIDTH 1280
# define RESOLUTION 0.625
# define VIEW_ANGLE 60
# define SEMI_ANGLE 30
# define BLOCK_SIZE 64
# define SPD_MAX 30
# define SPD_MIN 10
# define ROT_SPD 10
# define JMP_SPD 2
# define JMP_MAX 18
# define FALL_SPD 3
# define TALL_MAX 32
# define TALL_MIN 16
# define RAD (M_PI / 180)
# define PIX2 (M_PI * 2)
# define PI_2 (M_PI / 2)
# define PI_4 (M_PI / 4)

typedef struct		s_obj
{
	char			type;
	char			nbr;
	double			base;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_pln
{
	char			type;
	char			nbr;
	int				pts;
	double			p[4][3];
	struct s_pln	*next;
}					t_pln;

typedef struct		s_block
{
	t_pln			*pln;
	t_obj			*obj;
}					t_block;

typedef struct		s_map
{
	int				xblock;
	int				yblock;
	double			xmin;
	double			xmax;
	double			ymin;
	double			ymax;
	double			zmin;
	double			zmax;
	double			xpos0;
	double			ypos0;
	double			zpos0;
	double			zrot0;
	double			xpos;
	double			ypos;
	double			zpos;
	double			zrot;
	int				spd;
	int				mspd;
	int				sspd;
	int				jump;
	int				fall;
	int				crch;
	int				xtab;
	int				ytab;
	t_block			***tab;
}					t_map;

typedef struct		s_key
{
	int				forth[2];
	int				back[2];
	int				strafe_l;
	int				strafe_r;
	int				turn_l[2];
	int				turn_r[2];
	int				crouch;
	int				jump;
	int				use;
}					t_key;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*load;
	int				wid;
	int				hei;
	int				x;
	int				y;
	int				b;
	int				l;
	int				en;
	double			depth;
	char			*s;
	char			*name;
	int				fd;
	int				gnl;
	char			*line;
	char			*addr;
	t_key			*key;
	t_map			*map;
	double			rad_spd;
	double			rot;
	int				tall;
	int				spd;
	uint			color;
}					t_env;

int					ft_init_loading(char **s, int *i, int height);
void				ft_init_key(t_key *key);
void				ft_init_env(t_env *env);
void				ft_free_obj(t_obj *obj);
void				ft_free_pln(t_pln *pln);
void				ft_free_tab(t_block ***tab, size_t x, size_t y);
int					ft_free_env(t_env *env);
int					ft_put_error(char *error, t_env *env);
int					ft_perror(char *error, t_env *env);
int					ft_is_op(int c);
int					ft_is_val(int c);
int					ft_is_pln(int c);
int					ft_is_obj(int c);
int					ft_check_gnl(t_env *env, int y);
int					ft_put_data(t_map *map, char *s, size_t *l, double *data);
double				ft_put_operand(t_map *map, char *line, size_t *l);
void				ft_put_pln(t_env *env, size_t *l, t_pln *pln);
void				ft_put_obj(t_env *env, size_t *l, t_obj *obj);
t_pln				*ft_make_pln(t_block *block);
t_obj				*ft_make_obj(t_block *block);
int					ft_make_tab(t_map *map, int x, int y);
int					ft_make_key(t_env *env);
int					ft_load_map(t_env *env, size_t l, int *x, int *y);
int					ft_expose_hook(t_env *env);
int					ft_key_event(t_env *env);
int					ft_keypress_hook(int keycode, t_env *env);
int					ft_keyrelease_hook(int keycode, t_env *env);
void				ft_position(t_env *env);

#endif
