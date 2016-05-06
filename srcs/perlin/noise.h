/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:21:48 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/06 15:25:50 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
# define NOISE_H

#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define width 980
#define height 575

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

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_win2;
	void		*mlx_win3;
	void		*mlx_win4;
}				t_mlx;

#endif
