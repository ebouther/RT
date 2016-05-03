/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/03 10:07:53 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void		ft_in_light(t_work *work, t_env *e, t_color_res *col_res)
{
	t_list	*lst;
	double	tmp;
	t_color_res	col_add;
	double	angle_contact;

	col_add = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	ft_recalc_dir(work->light, work->ray, work->normal);
	lst = e->obj;
	while (lst)
	{
		tmp = ((t_obj *)(lst->content))->get_inters(work->ray, (t_obj *)(lst->content));
		if (tmp > ft_dist_light(&work->ray->pos, &work->light->pos) || tmp < 0 || (((t_obj *)(lst->content))->mat.refr > 0 && tmp > 0))
		{
			angle_contact = ft_angle_contact(work->ray, work->normal);
			col_add.diffuse.r += work->light->col.r * angle_contact * work->light->k;
			col_add.specular.r += work->light->col.r *
				ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) *
				work->obj->mat.brim;
			col_add.diffuse.g += work->light->col.g * angle_contact * work->light->k;
			col_add.specular.g += work->light->col.g *
				ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) *
				work->obj->mat.brim;
			col_add.diffuse.b += work->light->col.b * angle_contact * work->light->k;
			col_add.specular.b += work->light->col.b *
				ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) *
				work->obj->mat.brim;
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

t_color		*ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj)
{
	t_color_res	col_res;
	t_list		*lst;
	t_color		*final_col;
	t_work		work;
	double		refl;
	t_ray		*ray_refr;
	t_ray		*ray_refl;

	if (kk)
	{
		printf("\nray iter = %d\n",ray->iter);
		printf("ray_pos = %f, %f, %f\n",ray->pos.x, ray->pos.y, ray->pos.z);
		printf("ray_dir = %f, %f, %f\n",ray->dir.x, ray->dir.y, ray->dir.z);
		printf("cur obj : opac %f, refl %f\n",cur_obj->mat.opac, cur_obj->mat.refl);

	}
	work.obj = cur_obj;
	col_res = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	if ((final_col = (t_color*)malloc(sizeof(t_color))) == NULL)
		exit(-1);
	ft_bzero(final_col, sizeof(t_color));
	if (ray->iter >= NB_ITER)
		return ((t_color *)ft_memset(final_col, 0, sizeof(t_color)));
	work.ray = ft_recalc_ori(ray, t);
	if (kk)
		printf("new ori{%d] = %f, %f, %f \n",ray->iter, work.ray->pos.x, work.ray->pos.y, work.ray->pos.z);
	work.normal = cur_obj->get_normal(work.ray, cur_obj);
	if (kk)
		printf("normal[%d] = %f ,%f ,%f\n", ray->iter, work.normal->x, work.normal->y,work.normal->z);
	lst = e->light;
	if (cur_obj->mat.refr > 0)
	{
		ray_refr = ft_refr(ray, &work, &refl);
		col_res.refr = ft_contact(ray_refr, e);
		if (kk)
			printf("col_refr[%d] = %f, %f, %f\n",ray->iter, col_res.refr->r, col_res.refr->g, col_res.refr->b);
	}
	else
		refl = 0;
	if (cur_obj->mat.refl + refl > 0)
	{
		ray_refl = ft_refl(ray, &work);
		col_res.refl = ft_contact(ray_refl, e);
	}
	while (lst)
	{
		work.light = ((t_light *)(lst->content));
		ft_in_light(&work, e, &col_res);
		lst = lst->next;
	}
	if (kk)
	printf("col_diffu[%d] = %f, %f %f\n",ray->iter, col_res.diffuse.r,col_res.diffuse.g,col_res.diffuse.b);
	ft_bri_max(&col_res);
	final_col->r = ft_color_clip(e->amb * cur_obj->mat.col.r
				+ cur_obj->mat.col.r * col_res.diffuse.r * cur_obj->mat.opac + col_res.specular.r + cur_obj->mat.refr * (col_res.refr ? col_res.refr->r : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->r : 0));
	final_col->g = ft_color_clip(e->amb * cur_obj->mat.col.g 
				+ cur_obj->mat.col.g * col_res.diffuse.g * cur_obj->mat.opac + col_res.specular.g + cur_obj->mat.refr * (col_res.refr ? col_res.refr->g : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->g : 0));
	final_col->b = ft_color_clip(e->amb * cur_obj->mat.col.b
				+ cur_obj->mat.col.b * col_res.diffuse.b * cur_obj->mat.opac + col_res.specular.b + cur_obj->mat.refr * (col_res.refr ? col_res.refr->b : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->b : 0));
	ft_color_mode(final_col, e);
	free(work.normal);
	free(work.ray);
	//free(ray_refr);
	//free(ray_refl);
	if (kk)
	{	
		printf("final[%d] r = %f, g = %f, b= %f\n",ray->iter, final_col->r, final_col->g, final_col->b);
	}
	return (final_col);
}
