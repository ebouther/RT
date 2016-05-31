/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_antialiasing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 16:29:21 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 12:00:39 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void	ft_moyenne(int x, int y, char *buf, t_env *e)
{
	char	i;

	i = 0;
	while (i < 4)
	{
		e->data[(x * 4 + SIZE_W * 4 * y) + i] =
		((unsigned char)buf[(x * 4 + SIZE_W * 4 * y) + i] +
		(unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * y) + i] +
		(unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * y) + i] +
		(unsigned char)buf[(x * 4 + SIZE_W * 4 * (y + 1)) + i] +
		(unsigned char)buf[(x * 4 + SIZE_W * 4 * (y - 1)) + i] +
		(unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * (y + 1)) + i] +
		(unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * (y - 1)) + i] +
		(unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * (y + 1)) + i] +
		(unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * (y - 1)) + i]) / 9;
		i++;
	}
}

static int	ft_contrast2(unsigned char c[5])
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (abs(c[0] - c[i]) > 40)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_contrast(int x, int y, char *buf)
{
	unsigned char	col[5];
	char			i;

	i = 0;
	while (i < 4)
	{
		col[0] = (unsigned char)buf[(x * 4 + SIZE_W * 4 * y) + i];
		col[1] = (unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * y) + i];
		col[2] = (unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * y) + i];
		col[3] = (unsigned char)buf[(x * 4 + SIZE_W * 4 * (y + 1)) + i];
		col[4] = (unsigned char)buf[(x * 4 + SIZE_W * 4 * (y - 1)) + i];
		if (ft_contrast2(col))
			return (1);
		i++;
	}
	return (0);
}

void		ft_antialiasing(t_env *e)
{
	char	*buf;
	int		x;
	int		y;

	if ((buf = (char*)malloc(SIZE_W * SIZE_H * 4)) == NULL)
		ft_error_exit("malloc has failed in ft_antialiasing\n");
	ft_memcpy(buf, e->data, SIZE_W * SIZE_H * 4);
	x = 1;
	while (x < SIZE_W - 1)
	{
		y = 1;
		while (y < SIZE_H - 1)
		{
			if (ft_contrast(x, y, buf))
				ft_moyenne(x, y, buf, e);
			y++;
		}
		x++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	free(buf);
}
