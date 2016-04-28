/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/28 15:10:18 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

unsigned int	ft_contact(int x, int y, t_env *e)
{
	t_obj	*cur_obj;
	double	tmp;
	double	t;
	t_list	*lst;
	t_ray	*ray;
	int		k;

	t = FAR;
	ray = ft_calc_ray(x, y, e);
	tmp = 0;
	lst = e->obj;
	k = 0;
	if (e->xx == x && e->yy ==y)
		k = 1;
	while (lst)
	{
		tmp = ((t_obj *)(lst->content))->get_inters(ray, (t_obj *)lst->content, k);
		if (tmp < t && tmp >= 0)
		{
			t = tmp;
			cur_obj = (t_obj *)lst->content;
		}
		lst = lst->next;
	}
	if (t < FAR)
		return (ft_ishadow(e, ray, t, cur_obj));
	free(ray);
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
		while (y < SIZE_H)
		{
			couleur = ft_contact(x, y, e);
			ft_put_pixelle(x, y, &couleur, e);
			y++;
		}
		x++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void			ft_creat_img(t_env *e)
{
	e->img = mlx_new_image(e->mlx, SIZE_W, SIZE_H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->ls, &e->endian);
	ft_fill_img(e);
}

int				key_hook(int kc, t_env *e)
{
	printf("%d\n",kc);
	if (kc == 53)
		exit(0);
	else if (kc == 126)
	{
		((t_obj*)(e->obj->content))->dir.z =((t_obj*)(e->obj->content))->dir.z * cos (10.0 / 180.0 * M_PI);
		((t_obj*)(e->obj->content))->dir.y =((t_obj*)(e->obj->content))->dir.y * sin (10.0 / 180.0 * M_PI);
	}
	else if (kc == 125)
	{
		((t_obj*)(e->obj->content))->dir.z =((t_obj*)(e->obj->content))->dir.z * cos (-10.0 / 180.0 * M_PI);
		((t_obj*)(e->obj->content))->dir.y =((t_obj*)(e->obj->content))->dir.y * sin (-10.0 / 180.0 * M_PI);
	}
	else if (kc == 35)
		ft_make_screen(e, "img.ppm");
	ft_normalise(&((t_obj*)(e->obj->content))->dir);
	ft_fill_img(e);
	return (0);
}

int				mouse_hook(int b, int x, int y, t_env *e)
{
	if (b)
	{
		printf("x = %d, y = %d\n", x, y);
		e->xx = x;
		e->yy = y;
	}
	ft_fill_img(e);
	return (0);
}

void			ft_creat_win(t_env *e)
{
	e->pix_zero.x = ((double)HIGHT / 2.0) * e->cam.up.x - ((double)WIDTH / 2.0) * e->cam.right.x;
	e->pix_zero.y = ((double)HIGHT / 2.0) * e->cam.up.y - ((double)WIDTH / 2.0) * e->cam.right.y;
	e->pix_zero.z = ((double)HIGHT / 2.0) * e->cam.up.z - ((double)WIDTH / 2.0) * e->cam.right.z;
	e->mlx = mlx_init();
	e->xx = 0;
	e->yy = 0;
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_H, "RT");
	ft_creat_img(e);
	mlx_key_up_hook(e->win, &key_hook, e);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_loop(e->mlx);
}
