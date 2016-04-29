/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/28 17:23:15 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
t_color		*ft_contact(t_ray *ray, t_env *e)
{
	t_obj	*cur_obj;
	double	tmp;
	double	t;
	t_list	*lst;

	if (ray == NULL)
		return (NULL);

	t = FAR;
	tmp = 0;
	lst = e->obj;
	while (lst)
	{
		tmp = ((t_obj *)(lst->content))->get_inters(ray, (t_obj *)lst->content);
		if (tmp < t && tmp >= 0)
		{
			t = tmp;
			cur_obj = (t_obj *)lst->content;
		}
		lst = lst->next;
	}
	if (t < FAR)
		return (ft_ishadow(e, ray, t, cur_obj));
	return (NULL);
}

unsigned int	ft_rgbtoi(t_color *color)
{
	unsigned int res;

	if (color == NULL)
		return (0);
	res = (256 * 256 * (unsigned int)(color->r * 255) +
			256 * (unsigned int)(color->g * 255) +
			(unsigned int)(color->b * 255));
	free(color);
	return (res);
}

void			ft_fill_img(t_env *e)
{
	int				x;
	int				y;
	t_color			*couleur;
	t_ray			*ray;

	x = 0;
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_H)
		{
			ray = ft_calc_ray(x, y, e);
			couleur = ft_contact(ray, e);
			ft_put_pixelle(x, y, ft_rgbtoi(couleur), e);
			free(ray);
			y++;
		}
		x++;
	}
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
	if (kc == 53)
		exit(0);
	else if (kc == 126)
		((t_obj*)(e->obj->content))->dir.z += 10.0 / 180.0 * M_PI;
	else if (kc == 125)
		((t_obj*)(e->obj->content))->dir.z -= 10.0 / 180.0 * M_PI;
	else if (kc == 35)
		ft_make_screen(e, "img.ppm");
	ft_fill_img(e);
	return (0);
}

void			ft_creat_win(t_env *e)
{
	e->pix_zero.x = ((double)HIGHT / 2.0) * e->cam.up.x - ((double)WIDTH / 2.0) * e->cam.right.x;
	e->pix_zero.y = ((double)HIGHT / 2.0) * e->cam.up.y - ((double)WIDTH / 2.0) * e->cam.right.y;
	e->pix_zero.z = ((double)HIGHT / 2.0) * e->cam.up.z - ((double)WIDTH / 2.0) * e->cam.right.z;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_H, "RT");
	ft_creat_img(e);
	mlx_key_up_hook(e->win, &key_hook, e);
	mlx_loop(e->mlx);
}
