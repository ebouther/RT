/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 18:44:00 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void			ft_free(double **coul, t_env *e)
{
	int i;

	i = 0;
	while (i < e->nb_light)
	{
		free(coul[i]);
		i++;
	}
}

static void		ft_in_light(t_ligt *cur_light, t_env *e, t_ray *ray, t_color *col_res)
{
	int		b;
	t_list	*lst;
	double	tmp;
	t_color	col_add;
	double	angle_contact;

	col_add = (t_color){0, 0, 0};
	b = 0;
	ft_recalc_dir(cur_light, ray);
	lst = e->obj;
	while (lst)
	{
		tmp = ((t_obj *)(lst->content))->get_inters(ray, (t_obj *)(lst->content));
		if (tmp > ft_dist_light(&ray->pos, &cur_light->pos) && tmp < 0)
		{
			angle_contact = ft_angle_contact(ray, (t_obj *)(lst->content));
			col_add.r += cur_light->col.r * (angle_contact +
				ft_fpower(ft_brillance(e, e->ray.obj), 20) *
				e->obj[e->ray.obj].brim);
			col_add.g += cur_light->col.g * (angle_contact +
				ft_fpower(ft_brillance(e, e->ray.obj), 20) *
				e->obj[e->ray.obj].brim);
			col_add.b += cur_light->col.b * (angle_contact +
				ft_fpower(ft_brillance(e, e->ray.obj), 20) *
				e->obj[e->ray.obj].brim);
			if (!b)
				b = 1;
		}
		lst = lst->next;
	}
	if (b)
	{
		col_res->r += col_add.r;
		col_res->g += col_add.g;
		col_res->b += col_add.b;
	}
}

static void		ft_bri_max(t_color *colres)
{
	if (colres.r > 1)
		colres.r = 1;
	if (colres.g > 1)
		colres.g = 1;
	if (colres.b > 1)
		colres.b = 1;
}

unsigned int	ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj)
{
	t_color	*col_res;
	t_list	*lst;
	t_ray	*ray_diff;

	col_res.r = 0;
	col_res.g = 0;
	col_res.b = 0;
	ray_diff = t_recalc_ori(ray, t);
	lst = e->light;
	while (lst)
	{
		ft_in_light(lst, e, &ray_diff[0], clo_res);
		lst = lsr->next;
	}
	ft_bri_max(colres);
	return (65536 * (unsigned int)((cur_obj->mat.col.r * 255) * col_res.r)
			+ 256 * (unsigned int)((cur_obj->mat.col.g * 255) * col_res.g)
			+ (unsigned int)((cur_obj->mat.col.b * 255) * col_res.b));
}
