/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_correction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:51:46 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/27 12:16:49 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static unsigned char	ft_med(unsigned char tab[9])
{
	unsigned char	tmp;
	int				i;
	int				j;
	int				k;

	i = 0;
	while (i < 9)
	{
		j = -1;
		k = 1;
		while (++j < 8)
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j + 1];
				tab[j + 1] = tab[j];
				tab[j] = tmp;
				k = 0;
			}
		if (k)
			break ;
		i++;
	}
	return (tab[5]);
}

static void				ft_median(int x, int y, char *buf, t_env *e)
{
	char			i;
	unsigned char	tab[9];

	i = 0;
	while (i < 4)
	{
		tab[0] = (unsigned char)buf[(x * 4 + SIZE_W * 4 * y) + i];
		tab[1] = (unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * y) + i];
		tab[2] = (unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * y) + i];
		tab[3] = (unsigned char)buf[(x * 4 + SIZE_W * 4 * (y + 1)) + i];
		tab[4] = (unsigned char)buf[(x * 4 + SIZE_W * 4 * (y - 1)) + i];
		tab[5] = (unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * (y + 1)) + i];
		tab[6] = (unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * (y - 1)) + i];
		tab[7] = (unsigned char)buf[((x - 1) * 4 + SIZE_W * 4 * (y + 1)) + i];
		tab[8] = (unsigned char)buf[((x + 1) * 4 + SIZE_W * 4 * (y - 1)) + i];
		e->data[(x * 4 + SIZE_W * 4 * y) + i] = ft_med(tab);
		i++;
	}
}

void					ft_correction(t_env *e)
{
	char	*buf;
	int		x;
	int		y;

	if ((buf = (char*)malloc(SIZE_W * SIZE_H * 4)) == NULL)
		ft_error_exit("malloc has failed in ft_correction\n");
	ft_memcpy(buf, e->data, SIZE_W * SIZE_H * 4);
	x = 1;
	while (x < SIZE_W - 1)
	{
		y = 1;
		while (y < SIZE_H - 1)
		{
			ft_median(x, y, buf, e);
			y++;
		}
		x++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	free(buf);
}
