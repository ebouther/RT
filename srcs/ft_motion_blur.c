/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_motion_blur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:07:26 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/01 14:03:20 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int		ft_sur_droite(int xy[2], int xy_end[2], int x_start, int y_start)
{
	if (x_start != xy_end[0])
		if (xy[0] == xy[1] * (y_start - xy_end[1]) / (x_start - xy_end[0])
		+ y_start - x_start * (y_start - xy_end[1]) / (x_start - xy_end[0]))
			return (1);
	if (y_start != xy_end[1])
		if (xy[0] == xy[1] * (x_start - xy_end[0]) / (y_start - xy_end[1])
		+ x_start - y_start * (x_start - xy_end[0]) / (y_start - xy_end[1]))
			return (1);
	return (0);
}

void	ft_flou(t_env *e, int xy[2], int xy_end[2], int xy_start[2])
{
	double	f;
	double	p;

	if ((p = sqrt(carre(xy_end[0] - xy_start[0])
	+ carre(xy_end[1] - xy_start[1]))))
		f = sqrt(carre(xy_start[0] - xy[0]) + carre(xy_start[1] - xy[1])) / p;
	else
		return ;
	e->data2[xy[0] * 4 + 4 * xy[1] * SIZE_W] +=
			(unsigned char)(e->data[xy_start[0] * 4 + 4
			* xy_start[1] * SIZE_W] / p / p);
	e->data2[xy[0] * 4 + 4 * xy[1] * SIZE_W + 1] +=
			(unsigned char)(e->data[xy_start[0] * 4 + 4
			* xy_start[1] * SIZE_W + 1] / p / p);
	e->data2[xy[0] * 4 + 4 * xy[1] * SIZE_W + 2] +=
			(unsigned char)(e->data[xy_start[0] * 4 + 4
			* xy_start[1] * SIZE_W + 2] / p / p);
	e->data2[xy[0] * 4 + 4 * xy[1] * SIZE_W + 3] -=
			(unsigned char)(255 * (1 - f * f * f) / p);
}

void	ft_mot_pix(int x_start, int y_start, t_vec3 speed, t_env *e)
{
	int y_end;
	int x_end;
	int xy[2];
	int	dx;
	int	dy;

	x_end = x_start - (int)scal(e->cam.right, speed);
	y_end = y_start + (int)scal(e->cam.up, speed);
	xy[0] = x_start;
	dx = (x_start <= x_end ? 1 : -1);
	dy = (y_start <= y_end ? 1 : -1);
	while (xy[0] != x_end + dx)
	{
		xy[1] = y_start;
		while (xy[1] != y_end + dy)
		{
			if (ft_sur_droite(xy, (int[2]){x_end, y_end}, x_start, y_start))
				ft_flou(e, xy, (int[2]){x_end, y_end},
				(int[2]){x_start, y_start});
			xy[1] += dy;
		}
		xy[0] += dx;
	}
}

void	ft_init_im(t_env *e)
{
	int y;
	int x;

	x = 0;
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_H)
		{
			e->data2[4 * x + SIZE_W * 4 * y] = 0;
			e->data2[4 * x + SIZE_W * 4 * y] = 0;
			e->data2[4 * x + SIZE_W * 4 * y] = 0;
			e->data2[4 * x + SIZE_W * 4 * y + 3] = 255;
			y++;
		}
		x++;
	}
}

void	ft_motion_blur(t_env *e)
{
	int x_start;
	int y_start;

	e->img2 = mlx_new_image(e->mlx, SIZE_W, SIZE_H);
	e->data2 = mlx_get_data_addr(e->img2, &e->bpp, &e->ls, &e->endian);
	ft_init_im(e);
	x_start = -1;
	while (++x_start < SIZE_W)
	{
		y_start = -1;
		while (++y_start < SIZE_H)
		{
			if (e->pix[x_start + y_start * SIZE_W].obj)
			{
				if (e->pix[x_start + y_start * SIZE_W].obj->speed.x ||
				e->pix[x_start + y_start * SIZE_W].obj->speed.y ||
				e->pix[x_start + y_start * SIZE_W].obj->speed.z)
					ft_mot_pix(x_start, y_start,
					e->pix[x_start + y_start * SIZE_W].obj->speed, e);
			}
		}
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img2, 0, 0);
}
