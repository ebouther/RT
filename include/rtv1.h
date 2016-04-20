/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:49:49 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/20 16:05:51 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# define SIZE_W 1000
# define WIDTH 100
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

typedef struct	s_type
{
	int		sph;
	int		plan;
	int		cone;
	int		cyl;
}				t_type;

typedef struct	s_light
{
	double	centrex;
	double	centrey;
	double	centrez;
	double	colr;
	double	colg;
	double	colb;
}				t_light;

typedef struct	s_obj
{
	t_type	type;
	double	rayon;
	double	angle;
	double	centrex;
	double	centrez;
	double	centrey;
	double	normalx;
	double	normaly;
	double	normalz;
	double	directx;
	double	directy;
	double	directz;
	double	colr;
	double	colg;
	double	colb;
	double	brim;
	int		brip;
}				t_obj;

typedef	struct	s_cam
{
	double	posx;
	double	posy;
	double	posz;
	double	dirx;
	double	diry;
	double	dirz;
	double	upx;
	double	upy;
	double	upz;
	double	rightx;
	double	righty;
	double	rightz;
	double	distfo;
}				t_cam;

typedef struct	s_ray
{
	double	x;
	double	y;
	double	z;
	double	oeilx;
	double	oeily;
	double	oeilz;
	double	orix;
	double	oriy;
	double	oriz;
	double	t;
	int		obj;
}				t_ray;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		power;
	t_cam	cam;
	t_obj	*obj;
	t_light	*light;
	t_ray	ray;
	int		nb_obj;
	int		nb_light;
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
