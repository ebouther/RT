/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/20 15:02:23 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned int	ft_contact(int x, int y, t_env *e)
{
	int		i;
	double	tmp;

	ft_calc_ray(x, y, e);
	i = 0;
	tmp = 0;
	e->ray.t = 1000000000;
	while (i < e->nb_obj)
	{
		tmp = ft_dist(i, e);
		if (tmp < e->ray.t && tmp >= 0)
		{
			e->ray.obj = i;
			e->ray.t = tmp;
		}
		i++;
	}
	if (e->ray.t < 1000000000)
		return (ft_ishadow(e));
	return (0);
}

void			ft_fill_img(t_env *e)
{
	int				x;
	int				y;
	unsigned int	couleur;

	x = 0;
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_W)
		{
			couleur = ft_contact(x, y, e);
			ft_put_pixelle(x, y, &couleur, e);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void			ft_creat_img(t_env *e)
{
	int	bpp;
	int endian;
	int ls;

	bpp = 4;
	endian = 0;
	ls = 4 * 1000;
	e->img = mlx_new_image(e->mlx, 1000, 1000);
	e->data = mlx_get_data_addr(e->img, &bpp, &ls, &endian);
	ft_fill_img(e);
}

int				key_hook(int kc)
{
	if (kc == 53)
		exit(0);
	return (0);
}

void			ft_creat_win(t_env *e)
{
	e->power = 1;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_W, "trV1");
	ft_creat_img(e);
	mlx_key_up_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
}
