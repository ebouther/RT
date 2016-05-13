/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:21:48 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/13 15:07:26 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
# define NOISE_H

#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>

#define WIDTH 1500
#define HEIGHT 1000

typedef struct	s_color
{
	char		r;
	char		g;
	char		b;
}				t_color;

typedef struct	s_img
{
	void		*mlx_img;
	int			bpp;
	int			size_line;
	int			endian;
	char		*data;
}				t_img;

typedef struct	s_smooth
{
	double		fract_x;
	double		fract_y;
	double		value;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}				t_smooth;

typedef struct	s_wood
{
	t_color		c;
	double		x_val;
	double		y_val;
	double		dist_val;
	double		sine_val;
	int			x;
	int			y;
}				t_wood;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	double		**noise;
}				t_mlx;

t_color			get_pixel_color(char *data, int x, int y);
void			put_pixel(char **data, int x, int y, int color);
int				ft_hook_key(int keycode, t_mlx *m);

void			generate_noise(double ***noise);
double			smooth_noise(double x, double y, double ***noise);
double			turbulence(double x, double y, double size, double ***noise);
char			*gen_noise(double size, t_mlx *m);
char			*gen_wood(double xy_period, double turb_power, double turb_size, t_mlx *m);

#endif
