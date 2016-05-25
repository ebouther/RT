/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_celshading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 17:31:31 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/23 16:51:29 by jbelless         ###   ########.fr       */
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
			if (e->pix[x + x1 + SIZE_W * (y + y1)].obj != tmp)
				return (1);
			y1++;
		}
		x1++;
	}
	return (0);
}

void	ft_celshading(t_env *e)
{
	int		x;
	int		y;

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
				e->data[(x * 4 + SIZE_W * 4 * y) + 3] = 0;
			}
			else
			{
				if ((unsigned char)e->data[(x * 4 + SIZE_W * 4 * y)] < 240)
					e->data[(x * 4 + SIZE_W * 4 * y)] = ((e->data[(x * 4 + SIZE_W * 4 * y)] / 30) + 1) * 30;
				if ((unsigned char)e->data[(x * 4 + SIZE_W * 4 * y) + 1] < 240)
					e->data[(x * 4 + SIZE_W * 4 * y) + 1] = ((e->data[(x * 4 + SIZE_W * 4 * y) + 1] / 30) + 1) * 30;
				if ((unsigned char)e->data[(x * 4 + SIZE_W * 4 * y) + 2] < 240)
					e->data[(x * 4 + SIZE_W * 4 * y) + 2] = ((e->data[(x * 4 + SIZE_W * 4 * y) + 2] / 30) + 1) * 30;
				if ((unsigned char)e->data[(x * 4 + SIZE_W * 4 * y) + 3] < 240)
					e->data[(x * 4 + SIZE_W * 4 * y) + 3] = ((e->data[(x * 4 + SIZE_W * 4 * y) + 3] / 30) + 1) * 30;
			}
			y++;
		}
		x++;
	}	
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}
