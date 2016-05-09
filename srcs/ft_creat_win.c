/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/09 17:04:25 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_color		*ft_contact(t_ray *ray, t_env *e)
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
			cur_obj = tmp->obj;
		}
		lst = lst->next;
	}
	t_color	*sdf;
	sdf = malloc(sizeof(t_color));
	sdf->r = cur_obj->mat.col.r;
	sdf->g = cur_obj->mat.col.g;
	sdf->b = cur_obj->mat.col.b;
	if (t < FAR)
		return (sdf);
	//	return (ft_ishadow(e, ray, t, cur_obj));
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
			kk = 0;
			if (e->xx == x && e->yy == y)
				kk = 1;
			ray = ft_calc_ray(x, y, e);
			couleur = ft_contact(ray, e);
			ft_put_pixelle(x, y, ft_rgbtoi(couleur), e);
			free(ray);
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
	else if (kc == 35)
		ft_make_screen(e, "img.ppm");
	else if (kc == 0)
		ft_antialiasing(e);
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
	e->xx = 0;
	e->yy = 0;
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_H, "RT");
	ft_creat_img(e);
	mlx_key_up_hook(e->win, &key_hook, e);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_loop(e->mlx);
}
