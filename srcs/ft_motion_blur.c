/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_motion_blur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:07:26 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 14:22:42 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int	ft_sur_droite(int x, int y, int x_end, int y_end, int x_start, int y_start)
{
	if (x_start != x_end)
		if (y == x * (y_start - y_end) / (x_start - x_end) + y_start - x_start * (y_start - y_end) / (x_start - x_end))
			return (1);
	if (y_start != y_end)
		if (x == y * (x_start - x_end) / (y_start - y_end) + x_start - y_start * (x_start - x_end) / (y_start - y_end))
			return (1);
	return (0);
}

void	ft_flou(t_env *e, int x, int y, int x_end, int y_end, int x_start, int y_start)
{
	double	f;
	double	p;

	if ((p = sqrt(carre(x_end - x_start) + carre(y_end - y_start))))
		f = sqrt(carre(x_start - x) + carre(y_start - y)) / p;
	else
		return;
	e->data2[x * 4 + 4 * y * SIZE_W] += (unsigned char)(e->data[x_start * 4 + 4 * y_start * SIZE_W] * f / p) ;
	e->data2[x * 4 + 4 * y * SIZE_W + 1] += (unsigned char)(e->data[x_start * 4 + 4 * y_start * SIZE_W + 1] * f / p);
	e->data2[x * 4 + 4 * y * SIZE_W + 2] += (unsigned char)(e->data[x_start * 4 + 4 * y_start * SIZE_W + 2] * f / p);
	e->data2[x * 4 + 4 * y * SIZE_W + 3] -= (unsigned char)(255 * (1 - f * f * f) / p);

}

void	ft_mot_pix(int x_start, int y_start, t_vec3 speed, t_env *e)
{
	int y_end;
	int x_end;
	int x;
	int y;
	int	dx;
	int	dy;

	x_end = x_start - (int)scal(e->cam.right, speed);
	y_end = y_start + (int)scal(e->cam.up, speed);
	x = x_start;
	dx = (x_start <= x_end ? 1 : -1);
	dy = (y_start <= y_end ? 1 : -1);
	while (x != x_end + dx)
	{
		y = y_start;
		while (y != y_end + dy)
		{
			if (ft_sur_droite(x, y, x_end, y_end, x_start, y_start))
				ft_flou(e, x, y, x_end, y_end, x_start, y_start);	
			y += dy;
		}
		x += dx;
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
	x_start = 0;
	while (x_start < SIZE_W)
	{
		y_start = 0;
		while (y_start < SIZE_H)
		{
			if (e->pix[x_start + y_start * SIZE_W].obj->speed.x || e->pix[x_start + y_start * SIZE_W].obj->speed.y || e->pix[x_start + y_start * SIZE_W].obj->speed.z)
				ft_mot_pix(x_start, y_start, e->pix[x_start + y_start * SIZE_W].obj->speed, e);
			y_start++;
		}
		x_start++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img2, 0, 0);
}
