/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:49:49 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 18:36:08 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define SIZE_W 1000
# define SIZE_H 1000
# define WIDTH 100
# define HIGHT 100
# define FAR 1000000000

# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

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

typedef struct s_mat
{
	t_color		col;
	double		brim;
	char		brip;
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
	double	colr;
	double	colg;
	double	colb;
}				t_light;

typedef struct	s_obj
{
	t_vec3	*(*get_normal)();
	double	(*get_inters)(t_ray *ray, t_obj *obj);
	double	rayon;
	double	angle;
	t_vec3	pos;
	t_vec3	norm;
	t_vec3	dir;
	t_mat	mat;
}				t_obj;

typedef	struct	s_cam
{
	t_vec3	pos;
	t_vec3	dir;
	t_vec3	up;
	t_vec3	right;
	double	distfo;
}				t_cam;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}				t_ray;

typedef struct	s_env
{
	int		bpp;
	int 	endian;
	int 	ls;
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	t_cam	cam;
	t_list	*obj;
	t_list	*light;
}				t_env;

void			ft_put_pixelle(int x, int y, unsigned int *c, t_env *e);
void			ft_creat_img(t_env *e);
void			ft_normalise(double *x, double *y, double *z);
double			ft_norm(double x, double y, double z);
double			carre(double x);
double			ft_equa_sec(double a, double b, double c);
void			ft_creat_win(t_env *e);
void			ft_stock_cam(t_env *e, char *line);
void			ft_stock_cone(t_env *e, char *line, int *nb);
void			ft_stock_plan(t_env *e, char *line, int *nb);
void			ft_stock_cyl(t_env *e, char *line, int *nb);
void			ft_stock_sphere(t_env *e, char *line, int *nb);
void			ft_stock_light(t_env *e, char *line, int *nb);
unsigned int	ft_ishadow(t_env *e);
void			ft_calc_ray(int x, int y, t_env *e);
void			ft_recalc_ori(t_env *e);
void			ft_recalc_dir(t_env *e, int i);
double			ft_dist(int i, t_env *e);
double			ft_dist_light(t_env *e, int i);
double			ft_angle_contact(t_env *e, int i);
double			ft_brillance(t_env *e, int i);
double			ft_dist(int i, t_env *e);

#endif
