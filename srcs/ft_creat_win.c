/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/10 15:40:59 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_color		*ft_contact(t_ray *ray, t_env *e, t_obj **obj_pix)
{
	t_obj		*cur_obj;
	t_obj_col	*tmp;
	double		t;
	t_list		*lst;

	if (ray == NULL)
		return (NULL);
	t = FAR;
	lst = e->obj;
	while (lst)
	{
		tmp = ft_get_inters(lst->content, ray);
		if (tmp->t[0] < t)
		{
			t = tmp->t[0];
			if (obj_pix)
				*obj_pix = ((t_obj *)lst->content);
			cur_obj = tmp->obj;
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
			kk = 0;
			if (e->xx == x && e->yy == y)
				kk = 1;
			ft_put_pixelle(x, y, ft_rgbtoi(e->pix[x + y * SIZE_W].col), e);
			y++;
		}
		x++;
	}
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void			ft_fill_img(t_env *e)
{
	int				x;
	int				y;
	t_ray			*ray;

	x = 0;
	if ((e->pix = (t_pix*)malloc(sizeof(t_pix) * SIZE_W * SIZE_H)) == NULL)
		ft_error_exit("Error: malloc failed in ft_fill im.\n");
	while (x < SIZE_W)
	{
		y = 0;
		while (y < SIZE_H)
		{
			kk = 0;
			if (e->xx == x && e->yy == y)
				kk = 1;
			ray = ft_calc_ray(x, y, e);
			e->pix[x + y * SIZE_W].col = ft_contact(ray, e, &e->pix[x + y * SIZE_W].obj);
			free(ray);
			y++;
		}
		x++;
	}
	ft_print_img(e);
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
	else if (kc == 35)
		ft_make_screen(e, "img.ppm");
	else if (kc == 0)
		ft_antialiasing(e);
	else if (kc == 8)
		ft_celshading(e);
	return (0);
}

int				mouse_hook(int b, int x, int y, t_env *e)
{
	if (b)
	{
		e->xx = x;
		e->yy = y;
	}
	printf("x = %d,x = %d\n",x,y);
	ft_fill_img(e);
	return (1);
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
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_loop(e->mlx);
}
