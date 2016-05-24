/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/24 11:44:26 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void		ft_in_light(t_work *work, t_env *e, t_color_res *col_res)
{
	t_list	*lst;
	t_obj_col *obj;
	t_color_res	col_add;
	double	angle_contact;
	double tmp;
	t_color	filtre;

	col_add = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	ft_recalc_dir(work->light, work->ray, work->normal);
	lst = e->obj;
	filtre = (t_color){work->light->col.r, work->light->col.g, work->light->col.b};
	while (lst)
	{
		obj = ft_get_inters(lst->content, work->ray);
		tmp = obj->t[0] > 0 ? obj->t[0] : obj->t[1];
		if (((t_nod *)(lst->content))->obj->mat.refr > 0 && tmp > 0 && tmp < ft_dist_light(&work->ray->pos, &work->light->pos))
		{
			filtre.r *= ((t_nod *)(lst->content))->obj->mat.col.r * ((t_nod *)(lst->content))->obj->mat.refr;
			filtre.g *= ((t_nod *)(lst->content))->obj->mat.col.g * ((t_nod *)(lst->content))->obj->mat.refr;
			filtre.b *= ((t_nod *)(lst->content))->obj->mat.col.b * ((t_nod *)(lst->content))->obj->mat.refr;
		}
		else if (!(tmp > ft_dist_light(&work->ray->pos, &work->light->pos) || tmp < 0))
			break;
		lst = lst->next;
	}
	if (!lst)
	{
		angle_contact = ft_angle_contact(work->ray, work->normal);
		col_add.diffuse.r += filtre.r * angle_contact * work->light->k;
		col_add.specular.r += filtre.r * ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) * work->obj->mat.brim;
		col_add.diffuse.g += filtre.g * angle_contact * work->light->k;
		col_add.specular.g += filtre.g * ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) * work->obj->mat.brim;
		col_add.diffuse.b += filtre.b * angle_contact * work->light->k;
		col_add.specular.b += filtre.b * ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) * work->obj->mat.brim;
		col_res->diffuse.r += col_add.diffuse.r;
		col_res->specular.r += col_add.specular.r;
		col_res->diffuse.g += col_add.diffuse.g;
		col_res->specular.g += col_add.specular.g;
		col_res->diffuse.b += col_add.diffuse.b;
		col_res->specular.b += col_add.specular.b;
	}
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

void	ft_color_mode(t_color *c, t_env *e)
{
	t_color	in;

	in.r = c->r;
	in.g = c->g;
	in.b = c->b;
	if (e->color_m == 1)
	{
		c->r = ft_color_clip(in.r * 0.393 + in.g * 0.769 + in.b * 0.189);
		c->g = ft_color_clip(in.r * 0.349 + in.g * 0.683 + in.b * 0.168);
		c->b = ft_color_clip(in.r * 0.272 + in.g * 0.534 + in.b * 0.131);
	}
	else if (e->color_m == 2)
	{
		c->r = ft_color_clip((in.r + in.g + in.b) / 3.0);
		c->g = c->r;
		c->b = c->r;
	}
}

static int	ft_checkerboard(t_ray *ray, double t)
{
	t_vec3	pos;

	pos = (t_vec3){ray->dir.x * t + ray->pos.x, ray->dir.y * t + ray->pos.y, ray->dir.z * t + ray->pos.z};
	if ((int)pos.y <= 0)
		pos.y--;
	if ((int)pos.x <= 0)
		pos.x--;
	if ((((int)pos.x + (int)pos.y) / 2) % 2 == 0)
		return (1);
	return (0);
}

t_color		*ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj)
{
	t_color_res	col_res;
	t_list		*lst;
	t_color		*final_col;
	t_work		work;
	double		refl;
	t_ray		*ray_refr;
	t_ray		*ray_refl;
	t_color		col;

	work.obj = cur_obj;
	col_res = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	if ((final_col = (t_color*)malloc(sizeof(t_color))) == NULL)
		exit(-1);
	ft_bzero(final_col, sizeof(t_color));
	col = cur_obj->mat.col;
	if (cur_obj->mat.grid == TRUE && ft_checkerboard(ray, t))
		col = (t_color){1, 1, 0};
	if (cur_obj->mat.tex.buf != NULL)
		ft_select_texture(ray, t, cur_obj, &col);
	if (ray->iter >= NB_ITER)
		return ((t_color *)ft_memset(final_col, 0, sizeof(t_color)));
	work.ray = ft_recalc_ori(ray, t);
	work.normal = cur_obj->get_normal(work.ray, cur_obj);
	lst = e->light;
	if (cur_obj->mat.refr > 0)
	{
		ray_refr = ft_refr(ray, &work, &refl);
		col_res.refr = ft_contact(ray_refr, e, NULL);
	}
	else
		refl = 0;
	if (cur_obj->mat.refl + refl > 0)
	{
		ray_refl = ft_refl(ray, &work);
		col_res.refl = ft_contact(ray_refl, e, NULL);
	}
	while (lst)
	{
		work.light = ((t_light *)(lst->content));
		ft_in_light(&work, e, &col_res);
		lst = lst->next;
	}
	ft_bri_max(&col_res);
	final_col->r = ft_color_clip(e->amb * col.r + col.r * col_res.diffuse.r * cur_obj->mat.opac + col_res.specular.r + cur_obj->mat.refr * (col_res.refr ? col_res.refr->r : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->r : 0));
	final_col->g = ft_color_clip(e->amb * col.g + col.g * col_res.diffuse.g * cur_obj->mat.opac + col_res.specular.g + cur_obj->mat.refr * (col_res.refr ? col_res.refr->g : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->g : 0));
	final_col->b = ft_color_clip(e->amb * col.b + col.b * col_res.diffuse.b * cur_obj->mat.opac + col_res.specular.b + cur_obj->mat.refr * (col_res.refr ? col_res.refr->b : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->b : 0));
	ft_color_mode(final_col, e);
	free(work.normal);
	free(work.ray);
	//free(ray_refr);
	//free(ray_refl);
	return (final_col);
}
