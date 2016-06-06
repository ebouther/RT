/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/06 10:07:55 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void			ft_creat_img(t_env *e)
{
	t_env		d[THREAD_NUM];
	pthread_t	thr[THREAD_NUM];
	int			pos;

	e->img = mlx_new_image(e->mlx, SIZE_W, SIZE_H);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->ls, &e->endian);
	if ((e->pix = (t_pix*)malloc(sizeof(t_pix) * SIZE_W * SIZE_H)) == NULL)
		ft_error_exit("Error: malloc failed in ft_fill_img.\n");
	init_tex(e);
	pos = 0;
	while (pos < THREAD_NUM)
	{
		ft_memcpy(&d[pos], e, sizeof(t_env));
		d[pos].start = pos;
		if (pthread_create(&thr[pos], NULL, ft_fill_img, &d[pos]) != 0)
			ft_error_exit("THREAD ERROR.\n");
		pos++;
	}
	pos = 0;
	while (pos < THREAD_NUM)
		pthread_join(thr[pos++], NULL);
	ft_print_img(e);
}

int				key_hook(int kc, t_env *e)
{
	if (kc == 53)
		exit(0);
	else if (kc == 35)
		ft_make_screen(e, "img.ppm");
	else if (kc == 0)
		ft_antialiasing(e);
	else if (kc == 14)
		ft_correction(e);
	else if (kc == 8)
		ft_celshading(e);
	else if (kc == 46)
		ft_motion_blur(e);
	return (0);
}

int				mouse_hook(int b, int x, int y, t_env *e)
{
	if (b)
	{
		e->xx = x;
		e->yy = y;
	}
	return (1);
}

void			ft_creat_win(t_env *e)
{
	e->pix_zero.x = ((double)HIGHT / 2.0) * e->cam.up.x - ((double)WIDTH / 2.0)
		* e->cam.right.x;
	e->pix_zero.y = ((double)HIGHT / 2.0) * e->cam.up.y - ((double)WIDTH / 2.0)
		* e->cam.right.y;
	e->pix_zero.z = ((double)HIGHT / 2.0) * e->cam.up.z - ((double)WIDTH / 2.0)
		* e->cam.right.z;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, SIZE_W, SIZE_H, "RT");
	ft_creat_img(e);
	mlx_key_up_hook(e->win, &key_hook, e);
	mlx_mouse_hook(e->win, &mouse_hook, e);
	mlx_loop(e->mlx);
}
