/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:49:49 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/29 11:55:47 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

# define SIZE_W 1000
# define SIZE_H 1000
# define WIDTH 100
# define HIGHT 100
# define FAR 1000000000
# define NB_ITER 10

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct	s_color_res
{
	t_color		diffuse;
	t_color		specular;
	t_color		*refl;
	t_color		*refr;
}				t_color_res;

typedef struct s_mat
{
	t_color		col;
	double		brim;
	char		brip;
	double		i_opt;
	double		opac;
	double		refr;
	double		refl;
}				t_mat;

typedef struct	s_type
{
	int		sph;
	int		plan;
	int		cone;
	int		cyl;
}				t_type;

typedef struct	s_light
{
	t_vec3	pos;
	t_color	col;
	double	k;
}				t_light;

typedef	struct	s_cam
{
	t_vec3	pos;
	t_vec3	angle;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	double	distfo;
}				t_cam;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
	double	i_opt;
	int		iter;
}				t_ray;

typedef struct	s_obj
{
	t_vec3	*(*get_normal)();
	double	(*get_inters)(t_ray *ray, struct s_obj *obj);
	double	rayon;
	double	angle;
	t_vec3	pos;
	t_vec3	norm;
	t_vec3	dir;
	t_mat	mat;
}				t_obj;

typedef struct	s_env
{
	int		bpp;
	int 	endian;
	int 	ls;
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	t_vec3	pix_zero;
	t_cam	cam;
	t_list	*obj;
	t_list	*light;
	int		color_m;
	double	amb;
}				t_env;

typedef struct	s_work
{
	t_obj		*obj;
	t_light		*light;
	t_vec3		*normal;
	t_ray		*ray;
}				t_work;

void			ft_put_pixelle(int x, int y, unsigned int c, t_env *e);
void			ft_creat_img(t_env *e);
double			ft_equa_sec(double a, double b, double c);
void			ft_creat_win(t_env *e);
t_ray			*ft_refr(t_ray *ray, t_work *work, double *refl);
t_ray			*ft_refl(t_ray *ray, t_work *work);

/*
** Normals
*/
t_vec3			*normal_sphere(t_ray *ray, t_obj *obj);
t_vec3			*normal_cyl(t_ray *ray, t_obj *obj);
t_vec3			*normal_cone(t_ray *ray, t_obj *obj);
t_vec3			*normal_plan(t_ray *ray, t_obj *obj);

/*
** Intersects
*/
double			inters_sphere(t_ray *ray, t_obj *obj);
double			inters_cyl(t_ray *ray, t_obj *obj);
double			inters_cone(t_ray *ray, t_obj *obj);
double			inters_plan(t_ray *ray, t_obj *obj);

/*
** Math
*/
void			ft_normalise(t_vec3 *vec);
double			ft_norm(t_vec3 *vec);
double			carre(double x);
double			scal(t_vec3 a, t_vec3 b);
double			scal2(t_vec3 a);
t_vec3			*pro(double a, t_vec3 *d);

/*
** Utils.c
*/
char			*ft_strjoin_free(char *s1, char *s2);
double			ft_atod(char *s);
void			ft_error_exit(const char *error);

/*
** Parsing
*/
char			*ft_get_inner(char *str, char *obj, int *end_tag);
int				ft_set_vec3(char *obj, t_vec3 *vec3);
int				ft_set_color(char *obj, t_color *col);
int				ft_parse_scene(char *file, t_env *e);
int				ft_set_camera(char *camera, t_env *e);
int				ft_get_cylinders(char *objects, size_t len, t_env *e);
int				ft_get_spheres(char *objects, size_t len, t_env *e);
int				ft_get_cones(char *objects, size_t len, t_env *e);
int				ft_get_planes(char *objects, size_t len, t_env *e);
int				ft_get_lights(char *lights, size_t len, t_env *e);
int				ft_set_config(char *config, t_env *e);
void			ft_set_mat(char *mat, t_obj *obj);

t_ray			*ft_calc_ray(int x, int y, t_env *e);
t_color			*ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj);
t_ray    		*ft_recalc_ori(t_ray *ray, double t);
void			ft_recalc_dir(t_light *light, t_ray *ray);
double			ft_dist(int i, t_env *e);
double			ft_dist_light(t_vec3 *ray_pos, t_vec3 *light_pos);
double			ft_angle_contact(t_ray *ray, t_vec3 *normal);
double			ft_dist(int i, t_env *e);
double			ft_brillance(t_vec3 *pos_cam, t_ray *ray, t_vec3 *normal);
t_color			*ft_contact(t_ray *ray, t_env *e);

void	ft_make_screen(t_env *e, char *name);

#endif
