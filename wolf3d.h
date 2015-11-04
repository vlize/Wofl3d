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
# define WIDTH_2 640
# define WIDTH_4 320
# define WIDTH3_4 960
# define WIDTH4 5120
# define HEIGHT 720
# define HEIGHT_2 360
# define HEIGHT_4 180
# define HEIGHT3_4 540
# define DEPTH 640
# define FOV 90
# define FOV_2 45
# define BLOCK_SIZE 256
# define TALL_MAX 128
# define TALL_MIN 64
# define SPD_MAX 32
# define SPD_MIN 16
# define JMP_MAX 72
# define JMP_SPD 9
# define FALL_SPD 12
# define ROT_SPD 5
# define RAD 0.0174532925199432
# define PI2 6.283185307179587
# define PI_2 1.570796326794897
# define PI_4 0.7853981633974482
# define INC_PIX WIDTH4

typedef struct		s_color
{
	char			c[4];
	int				hex;
}					t_color;

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
	char			color;
	int				nbr;
	int				hex;
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
	char			*tex;
	int				fd;
	int				xsky;
	int				ysky;
	int				csky[2];
	t_color			*color;
	int				sky[WIDTH * 4][HEIGHT];
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
	int				endian;
	char			*s;
	char			*name;
	char			*line;
	char			*addr;
	t_key			*key;
	t_map			*map;
	double			hypo[WIDTH];
	double			coef[WIDTH];
	double			angle[WIDTH];
	double			rad_spd;
	double			mrot;
	double			p[3];
	double			cam[3];
	int				i[2];
	int				tall;
	int				spd;
}					t_env;

int					ft_init_win(t_env *env);
void				ft_init_env(t_env *env);
void				ft_init_map(t_map *map);
void				ft_init_key(t_key *key);
void				ft_free_obj(t_obj *obj);
void				ft_free_pln(t_pln *pln);
void				ft_free_tab(t_block ***tab, size_t x, size_t y);
void				ft_free_map(t_map *map);
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
t_pln				*ft_make_pln(t_block *block);
t_obj				*ft_make_obj(t_block *block);
int					ft_make_coef(t_env *env);
int					ft_make_tab(t_map *map, int x, int y);
int					ft_make_key(t_env *env);
int					ft_load_map(t_env *env, size_t l, int *x, int *y);
int					ft_expose_hook(t_env *env);
int					ft_key_event(t_env *env);
int					ft_keypress_hook(int keycode, t_env *env);
int					ft_keyrelease_hook(int keycode, t_env *env);
int					ft_reset(t_env *env);
void				ft_window_limits(intmax_t *y0, intmax_t *y1);
void				ft_map_limits(double *p, t_map *map);
void				ft_angle_limits(double *angle);
void				ft_position(t_env *env);
void				ft_crash_check(t_env *env);
void				ft_raycasting(t_env *env);
void				ft_cast_xp(int *i, double *p1, double *k, t_env *env);
void				ft_cast_xn(int *i, double *p1, double *k, t_env *env);
void				ft_cast_yp(int *i, double *p1, double *k, t_env *env);
void				ft_cast_yn(int *i, double *p1, double *k, t_env *env);
void				ft_wall(int *i, double *p1, t_env *env);
void				ft_floor_ceiling(int *i, double *p1, t_env *env);
void				ft_set_pixel(int ymin, int ymax, int color, t_env *env);
double				*ft_collision(double *a, double *b, double *c, double *d);
int					ft_limit_xy(int *i, t_env *env);
int					ft_ray_cast(int *i, double *p1, t_env *env);
int					ft_cast0_x(int *i, double *p1, double *k, t_env *env);
int					ft_cast0_y(int *i, double *p1, double *k, t_env *env);
int					ft_load_skybox(t_env *env);
int					ft_load_tex(t_map *map, t_env *env);
t_color				*ft_perror0(char *s, t_env *env);
t_color				*ft_put_error0(char *s, t_env *env);
void				ft_search_line(int fd, int *gnl, char **line);
void				ft_set_skybox(int x, int y, int ymax, t_env *env);

#endif
