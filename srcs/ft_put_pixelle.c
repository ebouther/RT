/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixelle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:57:07 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/03 14:57:13 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned int	ft_rgbtoi(t_color *color)
{
	unsigned int res;

	if (color == NULL)
		return (0);
	res = (256 * 256 * (unsigned int)(color->r * 255) +
			256 * (unsigned int)(color->g * 255) +
			(unsigned int)(color->b * 255));
	return (res);
}

void			ft_print_img(t_env *e)
{
	int x;
	int y;

	x = 0;
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_H)
		{
			ft_put_pixelle(x, y, ft_rgbtoi(e->pix[x + y * SIZE_W].col), e);
			y++;
		}
		x++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}


void			ft_pixmalloc(t_pix *pix)
{
	int		i;
	int		j;

	i = 0;
	while (i < SIZE_H)
	{
		j = 0;
		while (j < SIZE_W)
		{
			pix[j + i * SIZE_W].col = (t_color *)ft_memalloc(sizeof(t_color));
			pix[j + i * SIZE_W].obj = NULL;
			j++;
		}
		i++;
	}
}

void	ft_put_pixelle(int x, int y, unsigned int couleur, t_env *e)
{
	unsigned char	*c;
	unsigned int	*ptrc;

	ptrc = &couleur;
	c = (unsigned char*)e->data + x * 4 + y * 4 * SIZE_W;
	*c = *((unsigned char*)ptrc);
	*(c + 1) = *((unsigned char*)ptrc + 1);
	*(c + 2) = *((unsigned char*)ptrc + 2);
	*(c + 3) = *((unsigned char*)ptrc + 3);
}
