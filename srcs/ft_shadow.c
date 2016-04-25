/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/25 16:21:57 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_in_light(t_light *cur_light, t_env *e, t_ray *ray, t_color_res *col_res, t_obj *cur_obj)
{
	t_list	*lst;
	double	tmp;
	t_color_res	col_add;
	double	angle_contact;
	t_vec3	*normal;

	col_add = (t_color_res){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	ft_recalc_dir(cur_light, ray);
	lst = e->obj;
	normal = cur_obj->get_normal(ray, cur_obj);
	while (lst)
	{
		tmp = ((t_obj *)(lst->content))->get_inters(ray, (t_obj *)(lst->content));
		if (tmp > ft_dist_light(&ray->pos, &cur_light->pos) || tmp < 0)
		{
			angle_contact = ft_angle_contact(ray, normal);
			col_add.diffuse.r += cur_light->col.r * angle_contact * cur_light->k;
			col_add.specular.r += cur_light->col.r *
				ft_fpower(ft_brillance(&e->cam.dir, ray, normal), 20) *
				cur_obj->mat.brim;
			col_add.diffuse.g += cur_light->col.g * angle_contact * cur_light->k;
			col_add.specular.g += cur_light->col.g *
				ft_fpower(ft_brillance(&e->cam.dir, ray, normal), 20) *
				cur_obj->mat.brim;
			col_add.diffuse.b += cur_light->col.b * angle_contact * cur_light->k;
			col_add.specular.b += cur_light->col.b *
				ft_fpower(ft_brillance(&e->cam.dir, ray, normal), 20) *
				cur_obj->mat.brim;
		}
		else
			break ;
		lst = lst->next;
	}
	if (!lst)
	{
		col_res->diffuse.r += col_add.diffuse.r;
		col_res->specular.r += col_add.specular.r;
		col_res->diffuse.g += col_add.diffuse.g;
		col_res->specular.g += col_add.specular.g;
		col_res->diffuse.b += col_add.diffuse.b;
		col_res->specular.b += col_add.specular.b;
	}
	free((void *)normal);
}

double	ft_color_clip(double color)
{
	return ((color < 1) ? color : 1);
}

static void		ft_bri_max(t_color_res *colres)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((((t_color *)colres) + i)->r > 1)
			(((t_color *)colres) + i)->r = 1;
		if (((t_color *)colres + i)->g > 1)
			((t_color *)colres + i)->g = 1;
		if (((t_color *)colres + i)->b > 1)
			((t_color *)colres + i)->b = 1;
		i++;
	}
}

unsigned int	ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj)
{
	t_color_res	col_res;
	t_list	*lst;
	t_ray	*ray_diff;

	col_res = (t_color_res){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	ray_diff = ft_recalc_ori(ray, t);
	lst = e->light;
	while (lst)
	{
		ft_in_light((t_light *)(lst->content), e, &ray_diff[0], &col_res, cur_obj);
		lst = lst->next;
	}
	ft_bri_max(&col_res);
	return (65536 * (unsigned int)(ft_color_clip(cur_obj->mat.ambiante * cur_obj->mat.col.r + cur_obj->mat.col.r * col_res.diffuse.r + col_res.specular.r) * 255)
			+ 256 * (unsigned int)(ft_color_clip(cur_obj->mat.ambiante * cur_obj->mat.col.g + cur_obj->mat.col.g  * col_res.diffuse.g + col_res.specular.g) * 255)
			+ (unsigned int)(ft_color_clip(cur_obj->mat.ambiante * cur_obj->mat.col.b + cur_obj->mat.col.b * col_res.diffuse.b + col_res.specular.b) * 255));
}
