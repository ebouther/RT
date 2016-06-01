/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 14:01:00 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/01 14:01:27 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

/*void		ft_get_touch(t_obj_col *tmp, t_obj *cur_obj, t_obj **obj_pix, double *t, t_env *e, t_ray *ray)
  {
  t_list		*lst;

  lst = e->obj;
  while (lst)
  {
  tmp = ft_get_inters(lst->content, ray);
  if (tmp->t[0] < *t && tmp->t[0] > 0)
  {
 *t = tmp->t[0];
 if (obj_pix)
 *obj_pix = ((t_obj *)lst->content);
 cur_obj = tmp->obj;
 }
 else if (tmp->t[1] < *t && tmp->t[1] > 0)
 {
 *t = tmp->t[1];
 if (obj_pix)
 *obj_pix = ((t_obj *)lst->content);
 cur_obj = tmp->obj;
 }
 lst = lst->next;
 }

 }*/

t_color		*ft_contact(t_ray *ray, t_env *e, t_obj **obj_pix)
{
	t_obj		*cur_obj;
	t_obj_col	*tmp;
	double		t;
	t_list		*lst;

	if (ray == NULL)
		return (NULL);
	t = FAR;
	//	ft_get_touch(tmp, cur_obj, obj_pix, &t, e, ray);
	lst = e->obj;
	while (lst)
	{
		tmp = ft_get_inters(lst->content, ray);
		if (tmp->t[0] < t && tmp->t[0] > 0)
		{
			t = tmp->t[0];
			if (obj_pix)
				*obj_pix = tmp->obj;
			cur_obj = tmp->obj;
		}
		else if (tmp->t[1] < t && tmp->t[1] > 0)
		{
			t = tmp->t[1];
			if (obj_pix)
				*obj_pix = tmp->obj;
			cur_obj = tmp->obj;
		}
		else
		{
			free(tmp->t);
			free(tmp);
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

void	ft_stock_size_tex(t_obj *cur_obj)
{
	t_norm_stock_size_tex	norm;

	norm.i = 0;
	norm.buf = NULL;
	if ((norm.fd = open(cur_obj->mat.tex.tex, O_RDONLY)) == -1)
		ft_error_exit("error: bad texture file path.\n");
	while (norm.i++ != 4)
		norm.res = get_next_line(norm.fd, &norm.buf);
	norm.split = ft_strsplit(norm.buf, ' ');
	norm.width = ft_strdup(norm.split[0]);
	norm.height = ft_strdup(norm.split[1]);
	norm.i = 0;
	while (norm.split[norm.i])
		ft_strdel(norm.split + norm.i++);
	free(norm.split);
	cur_obj->mat.tex.width1 = atoi(norm.width + 1);
	cur_obj->mat.tex.height1 = atoi(norm.height);
	ft_strdel(&norm.width);
	ft_strdel(&norm.height);
	close(norm.fd);
}

void	ft_init_tex_node(t_nod *node, t_env *e)
{
	if (node->op == empty)
	{
		if (node->obj->mat.tex.tex != NULL)
		{
			ft_stock_size_tex(node->obj);
			node->obj->mat.tex.img =
				mlx_xpm_file_to_image(e->mlx, node->obj->mat.tex.tex,
						&node->obj->mat.tex.width1,
						&node->obj->mat.tex.height1);
			node->obj->mat.tex.buf =
				mlx_get_data_addr(node->obj->mat.tex.img,
						&node->obj->mat.tex.bpp,
						&node->obj->mat.tex.ls,
						&node->obj->mat.tex.endian);
		}
	}
	else
	{
		ft_init_tex_node(node->l, e);
		ft_init_tex_node(node->r, e);
	}

}

void	init_tex(t_env *e)
{
	t_list	*lst;

	lst = e->obj;
	while (lst)
	{
		ft_init_tex_node(((t_nod*)(lst->content)), e);
		lst = lst->next;
	}
}

static void			ft_pixmalloc(t_pix *pix)
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

static void			*ft_fill_img(void *e)
{
	int				coor[2];
	int				start;
	int				end;
	t_ray			*ray;
	t_vec3			dist;
	int				k;
	t_color			*tmp_col;

	k = 0;
	start = floor((SIZE_W / THREAD_NUM * ((t_env *)e)->start));
	end = ceil((SIZE_W / THREAD_NUM) * (((t_env *)e)->start + 1));
	ft_pixmalloc(((t_env *)e)->pix);
	if (((t_env *)e)->color_m >= 3)
	{
		dist.x = ((t_env *)e)->cam.right.x * 0.6;
		dist.y = ((t_env *)e)->cam.right.y * 0.6;
		dist.z = ((t_env *)e)->cam.right.z * 0.6;
		((t_env *)e)->cam.pos.x -= dist.x;
		((t_env *)e)->cam.pos.y -= dist.y;
		((t_env *)e)->cam.pos.z -= dist.z;
	}
	while ((++k <= 2 && ((t_env *)e)->color_m >= 3) || k == 1)
	{
		coor[0] = start;
		while (coor[0] < end)
		{
			coor[1] = 0;
			while (coor[1] < SIZE_H)
			{
				kk = 0;
				if (((t_env *)e)->xx == coor[0] && ((t_env *)e)->yy == coor[1])
					kk = 1;
				ray = ft_calc_ray(coor[0], coor[1], ((t_env *)e));
				tmp_col = ft_contact(ray, e, &((t_env *)e)->pix[coor[0] +
						coor[1] * SIZE_W].obj);
				if (tmp_col)
				{
					((t_env *)e)->pix[coor[0] + coor[1] * SIZE_W].col->r += tmp_col->r;
					((t_env *)e)->pix[coor[0] + coor[1] * SIZE_W].col->g += tmp_col->g;
					((t_env *)e)->pix[coor[0] + coor[1] * SIZE_W].col->b += tmp_col->b;
					free(tmp_col);
				}
				free(ray);
				coor[1]++;
			}
			coor[0]++;
		}
		((t_env *)e)->cam.pos.x += 2 * dist.x;
		((t_env *)e)->cam.pos.y += 2 * dist.y;
		((t_env *)e)->cam.pos.z += 2 * dist.z;
		((t_env *)e)->color_m++;
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
	printf("%d\n",kc);
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
	ft_creat_img(e);
	printf("x = %d,y = %d\n",x,y);
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
