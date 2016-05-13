/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_motion_blur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:07:26 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/13 16:53:44 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>


int		max2(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int		min2(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	ft_sur_droite(int x1, int y1, int xf, int yf, int x, int y)
{
	if (x != xf)
		if (y1 == x1 * (y - yf) / (x - xf) + y - x * (y - yf) / (x - xf))
			return (1);
	if (y != yf)
		if (x1 == y1 * (x - xf) / (y - yf) + x - y * (x - xf) / (y - yf))
			return (1);
	return (0);
}

void	ft_flou(t_env *e, int x1, int y1, int xf, int yf, int x, int y)
{
	double	f;
	double	p;

	if ((p = sqrt(carre(xf - x) + carre(yf - y))))
		f = sqrt(carre(xf - x1) + carre(yf - y1)) / p;
	else
		f = 1;
//	f = pow(f, 0.1);
	e->data2[x1 * 4 + 4 * y1 * SIZE_W + 3] = (unsigned char)((1 - f) * 255);
	printf("x1 =%d,  y1 %d\n",x1,y1);
	e->data2[x1 * 4 + 4 * y1 * SIZE_W] = e->data[x * 4 + 4 * y * SIZE_W];
	e->data2[x1 * 4 + 4 * y1 * SIZE_W + 1] = e->data[x * 4 + 4 * y * SIZE_W + 1];
	e->data2[x1 * 4 + 4 * y1 * SIZE_W + 2] = e->data[x * 4 + 4 * y * SIZE_W + 2];

}

void	ft_mot_pix(int x, int y, t_vec3 mot, t_env *e)
{
	int yf;
	int xf;
	int x1;
	int y1;

	xf = x + (int)scal(e->cam.right, mot);
	yf = y - (int)scal(e->cam.up, mot);
	x1 = min2(xf ,x);
	while (x1 <= max2(x, xf))
	{
		y1 = min2(yf, y);
		while (y1 <= max2(y, yf))
		{
			if (ft_sur_droite(x1, y1, xf, yf, x, y))
			{
				ft_flou(e, x1, y1, xf, yf, x, y);	
			}
			y1++;
		}
		x1++;
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
			e->data2[4 * x + SIZE_W * 4 * y + 3] = 255;
			y++;
		}
		x++;
	}

}

void	ft_motion_blur(t_env *e)
{
	int x;
	int y;

	e->img2 = mlx_new_image(e->mlx, SIZE_W, SIZE_H);
	e->data2 = mlx_get_data_addr(e->img2, &e->bpp, &e->ls, &e->endian);
	ft_init_im(e);
	x = 0;
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_H)
		{
			if (e->pix[x + y * SIZE_W].obj->motion.x || e->pix[x + y * SIZE_W].obj->motion.y || e->pix[x + y * SIZE_W].obj->motion.z)
				ft_mot_pix(x, y, e->pix[x + y * SIZE_W].obj->motion, e);
			y++;
		}
		x++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_put_image_to_window(e->mlx, e->win, e->img2, 0, 0);
}
