/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/23 12:35:48 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void        ft_stock_size_tex(t_obj *cur_obj)
{
	int     fd;
	char    *buf;
	int     res;
	int     i;
	char    *width;
	char    *height;
	char	**split;

	i = 0;
	buf = NULL;
	if ((fd = open(cur_obj->mat.tex.tex, O_RDONLY)) == -1)
		ft_error_exit("error: bad texture file path.\n");
	while (i++ != 4)
		res = get_next_line(fd, &buf);
	split = ft_strsplit(buf, ' ');
	width = ft_strdup(split[0]);
	height = ft_strdup(split[1]);
	i = 0;
	while (split[i])
		ft_strdel(split + i++);
	free(split);
	cur_obj->mat.tex.width1 = atoi(width + 1);
	cur_obj->mat.tex.height1 = atoi(height);
	ft_strdel(&width);
	ft_strdel(&height);
	close(fd);
}

void    init_tex(t_env  *e)
{
	t_list  *lst;

	lst = e->obj;
	while (lst)
	{
		if (((t_nod *)(lst->content))->obj->mat.tex.tex != NULL)
		{
			ft_stock_size_tex(((t_nod *)lst->content)->obj);
			((t_nod *)lst->content)->obj->mat.tex.img = mlx_xpm_file_to_image(e->mlx, ((t_nod *)(lst->content))->obj->mat.tex.tex, &((t_nod *)(lst->content))->obj->mat.tex.width1, &((t_nod *)(lst->content))->obj->mat.tex.height1);
			((t_nod *)lst->content)->obj->mat.tex.buf = mlx_get_data_addr(((t_nod *)(lst->content))->obj->mat.tex.img, &((t_nod *)(lst->content))->obj->mat.tex.bpp,
															&((t_nod *)(lst->content))->obj->mat.tex.ls, &((t_nod *)(lst->content))->obj->mat.tex.endian);
		}
		lst = lst->next;
	}
}

static void			*ft_fill_img(void *e)
{
	int				x;
	int				y;
	int				start;
	int				end;
	t_ray			*ray;

	start = floor((SIZE_W / THREAD_NUM * ((t_env *)e)->start));
	end = ceil((SIZE_W / THREAD_NUM) * (((t_env *)e)->start + 1));
	x = start;
	while (x < end)
	{
		y = 0;
		while (y < SIZE_H)
		{
			kk = 0;
			if (((t_env *)e)->xx == x && ((t_env *)e)->yy == y)
				kk = 1;
			ray = ft_calc_ray(x, y, ((t_env *)e));
			((t_env *)e)->pix[x + y * SIZE_W].col = ft_contact(ray, e, &((t_env *)e)->pix[x + y * SIZE_W].obj);
			free(ray);
			y++;
		}
		x++;
	}
	pthread_exit(NULL);
}

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
