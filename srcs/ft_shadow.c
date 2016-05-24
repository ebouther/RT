/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/24 15:37:45 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_get_mat_col(t_color *col, t_obj *cur_obj, t_ray *ray, double t)
{
	*col = cur_obj->mat.col;
	if (cur_obj->mat.grid == TRUE && ft_checkerboard(ray, t))
		*col = (t_color){1, 1, 0};
	if (cur_obj->mat.tex.buf != NULL)
		ft_select_texture(ray, t, cur_obj, col);
}

void		ft_init_shadow(t_shadow *s, t_obj *cur_obj,
				t_ray *ray, double t)
{
	s->work.obj = cur_obj;
	s->col_res = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	if ((s->final_col = (t_color*)malloc(sizeof(t_color))) == NULL)
		exit(-1);
	ft_bzero(s->final_col, sizeof(t_color));
	ft_get_mat_col(&s->col, cur_obj, ray, t);
	s->work.ray = ft_recalc_ori(ray, t);
	s->work.normal = cur_obj->get_normal(s->work.ray, cur_obj);
}

void		ft_calc_final_col(t_env *e, t_color *final_col, t_color *col,
				t_obj *cur_obj, t_color_res *col_res, double refl)
{
	final_col->r = COLOR_CLIP(e->amb * col->r + col->r * col_res->diffuse.r
		* cur_obj->mat.opac + col_res->specular.r + cur_obj->mat.refr
		* (col_res->refr ? col_res->refr->r : 0) + (cur_obj->mat.refl + refl)
		* (col_res->refl ? col_res->refl->r : 0));
	final_col->g = COLOR_CLIP(e->amb * col->g + col->g * col_res->diffuse.g
		* cur_obj->mat.opac + col_res->specular.g + cur_obj->mat.refr
		* (col_res->refr ? col_res->refr->g : 0) + (cur_obj->mat.refl + refl)
		* (col_res->refl ? col_res->refl->g : 0));
	final_col->b = COLOR_CLIP(e->amb * col->b + col->b * col_res->diffuse.b
		* cur_obj->mat.opac + col_res->specular.b + cur_obj->mat.refr
		* (col_res->refr ? col_res->refr->b : 0) + (cur_obj->mat.refl + refl)
		* (col_res->refl ? col_res->refl->b : 0));
}

void		ft_refl_refr_calc(t_obj *cur_obj, t_shadow *s, t_ray *ray, t_env *e)
{
	if (cur_obj->mat.refr > 0)
	{
		s->ray_refr = ft_refr(ray, &s->work, &s->refl);
		s->col_res.refr = ft_contact(s->ray_refr, e, NULL);
	}
	else
		s->refl = 0;
	if (cur_obj->mat.refl + s->refl > 0)
	{
		s->ray_refl = ft_refl(ray, &s->work);
		s->col_res.refl = ft_contact(s->ray_refl, e, NULL);
	}
}

t_color		*ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj)
{
	t_shadow	s;

	s.lst = e->light;
	ft_init_shadow(&s, cur_obj, ray, t);
	if (ray->iter >= NB_ITER)
		return ((t_color *)ft_memset(s.final_col, 0, sizeof(t_color)));
	ft_refl_refr_calc(cur_obj, &s, ray, e);
	while (s.lst)
	{
		s.work.light = ((t_light *)(s.lst->content));
		ft_in_light(&s.work, e, &s.col_res);
		s.lst = s.lst->next;
	}
	ft_bri_max(&s.col_res);
	ft_calc_final_col(e, s.final_col, &s.col, cur_obj, &s.col_res, s.refl);
	ft_color_mode(s.final_col, e);
	free(s.work.normal);
	free(s.work.ray);
	return (s.final_col);
}
