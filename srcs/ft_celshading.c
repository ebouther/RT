/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_celshading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:31:31 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/13 15:15:13 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

int	ft_voisin(int x, int y, t_env *e)
{
	t_obj	*tmp;
	int		x1;
	int		y1;

	x1 = -1;
	tmp = e->pix[x + y * SIZE_W].obj;
	while (x1 < 2)
	{
		y1 = -1;
		while (y1 < 2)
		{
			if (e->pix[x + SIZE_W * y].col == NULL || e->pix[x + x1 + SIZE_W * (y + y1)].obj != tmp)
				return (1);
			y1++;
		}
		x1++;
	}
	return (0);
}

double	ft_cartoon(double col)
{
	if (col > 0.8)
		return (1.0);
	else if (col > 0.7)
		return (0.9);
	else if (col > 0.6)
		return (0.8);
	else if (col > 0.5)
		return (0.7);
	else if (col > 0.4)
		return (0.6);
	else if (col > 0.3)
		return (0.5);
	else if (col > 0.2)
		return (0.4);
	else if (col > 0.1)
		return (0.3);
	else if (col > 0.5)
		return (0.2);
	else 
		return (0.1);
}


void	ft_celshading(t_env *e)
{
	int		x;
	int		y;
	int		i;
	double	f;

	x = 1;
	while (x < SIZE_W - 1)
	{
		y = 1;
		while (y < SIZE_H - 1)
		{
			if (ft_voisin(x, y, e))
			{
				e->data[(x * 4 + SIZE_W * 4 * y)] = 0;
				e->data[(x * 4 + SIZE_W * 4 * y) + 1] = 0;
				e->data[(x * 4 + SIZE_W * 4 * y) + 2] = 0;
			}
			else 
			{
				f = ft_cartoon(fmax(e->pix[x + SIZE_W * y].col->r, fmax(e->pix[x + SIZE_W * y].col->g, e->pix[x + SIZE_W * y].col->b)));
				i = 0;
				while (i < 4)
				{
					e->data[(x * 4 + SIZE_W * 4 * y) + i] = (unsigned char)(e->data[(x * 4 + SIZE_W * 4 * y) + i] * f);
					i++;
				}
			}
			y++;
		}
		x++;
	}	
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}
