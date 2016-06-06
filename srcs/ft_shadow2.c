/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:27:18 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/06 12:01:29 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_light_col(t_color_res *col_res, t_work *work,
					t_color *filtre, t_env *e)
{
	t_color_res	col_add;
	double		angle_contact;

	col_add = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	angle_contact = ft_angle_contact(work->ray, work->normal);
	col_add.diffuse.r += filtre->r * angle_contact * work->light->new_k;
	col_add.specular.r += filtre->r * ft_fpower(ft_brillance(&e->cam.dir,
				work->ray, work->normal), 20) * work->obj->mat.brim;
	col_add.diffuse.g += filtre->g * angle_contact * work->light->new_k;
	col_add.specular.g += filtre->g * ft_fpower(ft_brillance(&e->cam.dir,
				work->ray, work->normal), 20) * work->obj->mat.brim;
	col_add.diffuse.b += filtre->b * angle_contact * work->light->new_k;
	col_add.specular.b += filtre->b * ft_fpower(ft_brillance(&e->cam.dir,
				work->ray, work->normal), 20) * work->obj->mat.brim;
	col_res->diffuse.r += col_add.diffuse.r;
	col_res->specular.r += col_add.specular.r;
	col_res->diffuse.g += col_add.diffuse.g;
	col_res->specular.g += col_add.specular.g;
	col_res->diffuse.b += col_add.diffuse.b;
	col_res->specular.b += col_add.specular.b;
}

void			ft_in_light(t_work *work, t_env *e, t_color_res *col_res)
{
	t_list		*lst;
	t_obj_col	*obj;
	double		tmp;
	t_color		filtre;

	lst = e->obj;
	ft_recalc_dir(work->light, work->ray, work->normal);
	filtre = (t_color){work->light->col.r, work->light->col.g,
		work->light->col.b};
	while (lst)
	{
		obj = ft_get_inters(lst->content, work->ray);
		tmp = obj->t[0] > 0 ? obj->t[0] : obj->t[1];
		if (obj->obj->mat.refr > 0 && tmp > 0
				&& tmp < ft_dist_light(&work->ray->pos, work->light))
			ft_calc_filtre(&filtre, obj->obj);
		else if (!(tmp > ft_dist_light(&work->ray->pos, work->light)
			|| tmp < 0))
			break ;
		lst = lst->next;
	}
	if (!lst)
		ft_light_col(col_res, work, &filtre, e);
}

void			ft_bri_max(t_color_res *colres)
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

void			ft_color_mode(t_color *c, t_env *e)
{
	t_color	in;

	in.r = c->r;
	in.g = c->g;
	in.b = c->b;
	if (e->color_m == 1)
	{
		c->r = COLOR_CLIP(in.r * 0.393 + in.g * 0.769 + in.b * 0.189);
		c->g = COLOR_CLIP(in.r * 0.349 + in.g * 0.683 + in.b * 0.168);
		c->b = COLOR_CLIP(in.r * 0.272 + in.g * 0.534 + in.b * 0.131);
	}
	else if (e->color_m == 2)
	{
		c->r = COLOR_CLIP((in.r + in.g + in.b) / 3.0);
		c->g = c->r;
		c->b = c->r;
	}
	else if (e->color_m == 3)
	{
		c->g = 0;
		c->b = 0;
	}
	else if (e->color_m == 4)
		c->r = 0;
}

void			ft_smooth_shadows(t_shadow *s, t_env *e)
{
	int			i[3];

	i[0] = 0;
	while (i[0] <= s->work.light->nb_light)
	{
		s->work.light->offset.y = -(s->work.light->nb_light
				* s->work.light->dist_light) / 2.0;
		i[1] = 0;
		while (i[1] <= s->work.light->nb_light)
		{
			s->work.light->offset.z = -(s->work.light->nb_light
					* s->work.light->dist_light) / 2.0;
			i[2] = 0;
			while (i[2]++ <= s->work.light->nb_light)
			{
				ft_in_light(&s->work, e, &s->col_res);
				s->work.light->offset.z += s->work.light->dist_light;
			}
			s->work.light->offset.y += s->work.light->dist_light;
			i[1]++;
		}
		s->work.light->offset.x += s->work.light->dist_light;
		i[0]++;
	}
}
