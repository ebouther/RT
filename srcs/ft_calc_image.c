/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 15:01:22 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/03 15:30:04 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_get_touched_obj(t_obj_col *tmp, t_obj **cur_obj, t_obj **obj_pix,
				double *t)
{
	if (tmp->t[0] < *t && tmp->t[0] > 0)
	{
		*t = tmp->t[0];
		if (obj_pix)
			*obj_pix = tmp->obj;
		*cur_obj = tmp->obj;
	}
	else if (tmp->t[1] < *t && tmp->t[1] > 0)
	{
		*t = tmp->t[1];
		if (obj_pix)
			*obj_pix = tmp->obj;
		*cur_obj = tmp->obj;
	}
	else
	{
		free(tmp->t);
		free(tmp);
	}
}

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
		ft_get_touched_obj(tmp, &cur_obj, obj_pix, &t);
		lst = lst->next;
	}
	if (t < FAR)
		return (ft_ishadow(e, ray, t, cur_obj));
	return (NULL);
}

void				*ft_fill_img(void *e)
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
