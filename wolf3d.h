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
# include <pthread.h>

# define WIDTH 1280
# define HEIGHT 800
# define WIDTH_2 (WIDTH / 2)
# define HEIGHT_2 (HEIGHT / 2)
# define WIDTH_4 (WIDTH / 4)
# define HEIGHT_4 (HEIGHT / 4)
# define WIDTH3_4 (WIDTH - WIDTH_2)
# define HEIGHT3_4 (HEIGHT - HEIGHT_2)
# define DEPTH 640
# define FOV 90
# define FOV_2 FOV / 2
# define BLOCK_SIZE WIDTH / 10
# define TALL_MAX BLOCK_SIZE / 2
# define TALL_MIN BLOCK_SIZE / 4
# define SPD_MAX BLOCK_SIZE / 8
# define SPD_MIN SPD_MAX / 2
# define JMP_MAX TALL_MIN * 1.125
# define JMP_SPD JMP_MAX / 8
# define FALL_SPD BLOCK_SIZE / 20
# define ROT_SPD 15
# define RAD (M_PI / 180)
# define PI2 (M_PI * 2)
# define PI_2 (M_PI / 2)
# define PI_4 (M_PI / 4)

typedef struct		s_obj
{
	char			type;
	int				nbr;
	double			base;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_pln
{
	char			type;
	int				nbr;
	uint			hex;
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
	double			xmax;
	double			ymax;
	double			zmin;
	double			zmax;
	double			p0[3];
	double			zrot0;
	double			p[3];
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
	int				fd;
	int				gnl;
	int				bpp;
	int				sl;
	int				en;
	char			*s;
	char			*name;
	char			*line;
	char			*addr;
	t_key			*key;
	t_map			*map;
	double			coef[WIDTH];
	double			angle[WIDTH];
	double			rad_spd;
	double			mrot;
	double			p[3];
	double			cam[3];
	int				i[2];
	int				tall;
	int				spd;
	void			*value[3];
	pthread_t		thread[3];
	pthread_mutex_t	mutex[4];
	uint			*draw;
	uint			color;
}					t_env;

int					ft_init_loading(char **s, int *i);
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
uint				ft_put_color(char c, int i);
double				ft_put_operand(t_map *map, char *line, size_t *l);
void				ft_put_pln(t_env *env, size_t *l, t_pln *pln);
void				ft_put_obj(t_env *env, size_t *l, t_obj *obj);
void				ft_make_coef(t_env *env);
t_pln				*ft_make_pln(t_block *block);
t_obj				*ft_make_obj(t_block *block);
int					ft_make_tab(t_map *map, int x, int y);
int					ft_make_key(t_env *env);
int					ft_load_map(t_env *env, size_t l, int *x, int *y);
int					ft_expose_hook(t_env *env);
int					ft_key_event(t_env *env);
int					ft_keypress_hook(int keycode, t_env *env);
int					ft_keyrelease_hook(int keycode, t_env *env);
int					ft_reset(t_env *env);
int					ft_init_thread(t_env *env);
void				ft_make_thread(t_env *env);
void				ft_map_limits(double *p, t_map *map);
void				ft_position(t_env *env);
void				ft_crash_check(t_env *env);
void				*ft_raycasting0(void *arg);
void				*ft_raycasting1(void *arg);
void				*ft_raycasting2(void *arg);
void				ft_raycasting3(t_env *env);
void				ft_trace_x(int *i, double *p1, double *k, t_env *env);
void				ft_trace_y(int *i, double *p1, double *k, t_env *env);
double				*ft_collision(double *a, double *b, double *c, double *d);

#endif
