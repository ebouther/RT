/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 10:56:28 by pboutin           #+#    #+#             */
/*   Updated: 2016/05/27 11:50:19 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_norm_tex		ft_texture_cone_norm(t_vec3 pos)
{
	t_norm_tex norm;

	norm.rayon = sqrt(pow(pos.x, 2) + pow(pos.z, 2));
	norm.z = pos.y;
	norm.teta = acos((pos.x) / norm.rayon);
	return (norm);
}

unsigned int	ft_texture_cone(t_ray *ray, double t, t_obj *cur_obj,
		t_color *col)
{
	t_norm_tex	norm;
	t_vec3		pos;

	pos = ft_norm_tex(ray, t, cur_obj, -18000);
	ft_norm_tex_rot(cur_obj, &pos);
	norm = ft_texture_cone_norm(pos);
	pos = ft_norm_tex(ray, t, cur_obj, cur_obj->mat.tex.height);
	ft_normalise(&cur_obj->dir);
	ft_norm_tex_rot(cur_obj, &pos);
	norm.zA = pos.y;
	pos = ft_norm_tex(ray, t, cur_obj, cur_obj->mat.tex.width);
	ft_norm_tex_rot(cur_obj, &pos);
	norm.zB = pos.y;
	norm.tetaA = acos(-1);
	norm.tetaB = acos(1);
	if (norm.teta < norm.tetaA &&
			norm.teta > norm.tetaB && norm.z < norm.zB && norm.z > norm.zA)
	{
		*col = ft_get_tex_color((int)((norm.teta - norm.tetaA) / (norm.tetaB -
norm.tetaA) * cur_obj->mat.tex.width1), (int)(cur_obj->mat.tex.height1 - (((
norm.z - norm.zA) / (norm.zB - norm.zA)) * cur_obj->mat.tex.height1)), cur_obj);
		return (1);
	}
	return (0);
}

t_norm_tex		ft_norm_tex_plan(t_ray *ray, double t, t_obj *cur_obj)
{
	t_norm_tex	norm;

	norm.z = 0;
	norm.y = 0;
	if (cur_obj->norm.x == 1 || cur_obj->norm.x == -1)
	{
		norm.z = ray->dir.z * t + ray->pos.z;
		norm.y = ray->dir.y * t + ray->pos.y;
	}
	else if (cur_obj->norm.z == 1 || cur_obj->norm.z == -1)
	{
		norm.z = ray->dir.x * t + ray->pos.x;
		norm.y = ray->dir.y * t + ray->pos.y;
	}
	else if (cur_obj->norm.y == 1 || cur_obj->norm.y == -1)
	{
		norm.z = ray->dir.x * t + ray->pos.x;
		norm.y = ray->dir.z * t + ray->pos.z;
	}
	norm.zB = cur_obj->mat.tex.off_x - cur_obj->mat.tex.width;
	norm.yB = cur_obj->mat.tex.off_y - cur_obj->mat.tex.height;
	return (norm);
}

unsigned int	ft_texture_plan(t_ray *ray, double t, t_obj *cur_obj,
		t_color *col)
{
	t_norm_tex	norm;

	norm = ft_norm_tex_plan(ray, t, cur_obj);
	if (norm.z < cur_obj->mat.tex.off_x && norm.z > norm.zB &&
			norm.y < cur_obj->mat.tex.off_y && norm.y > norm.yB)
	{
		*col = ft_get_tex_color((int)(((norm.z - norm.zB) / (
			cur_obj->mat.tex.off_x - norm.zB)) * cur_obj->mat.tex.width1),
				(int)(cur_obj->mat.tex.height1 - (((norm.y - norm.yB) /
					(cur_obj->mat.tex.off_y - norm.yB)) *
						cur_obj->mat.tex.height1)), cur_obj);
		return (1);
	}
	return (0);
}

int				ft_select_texture(t_ray *ray, double t, t_obj *cur_obj,
		t_color *col)
{
	if (cur_obj->get_inters == inters_cyl)
		ft_texture(ray, t, cur_obj, col);
	else if (cur_obj->get_inters == inters_cone)
		ft_texture_cone(ray, t, cur_obj, col);
	else if (cur_obj->get_inters == inters_sphere)
		ft_texture_sphere(ray, t, cur_obj, col);
	else if (cur_obj->get_inters == inters_plan)
		ft_texture_plan(ray, t, cur_obj, col);
	return (1);
}
