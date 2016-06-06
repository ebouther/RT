/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 11:07:47 by pboutin           #+#    #+#             */
/*   Updated: 2016/05/27 11:52:09 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				ft_texture(t_ray *ray, double t, t_obj *cur_obj, t_color *col)
{
	t_norm_tex	norm;
	t_vec3		pos;

	pos = ft_norm_tex(ray, t, cur_obj, -18000);
	ft_norm_tex_rot(cur_obj, &pos);
	norm.z = pos.y;
	norm.teta = acos((pos.x) / cur_obj->rayon);
	pos = ft_norm_tex(ray, t, cur_obj, cur_obj->mat.tex.height);
	ft_norm_tex_rot(cur_obj, &pos);
	norm.za = pos.y;
	pos = ft_norm_tex(ray, t, cur_obj, cur_obj->mat.tex.width);
	ft_norm_tex_rot(cur_obj, &pos);
	norm.zb = pos.y;
	norm.teta_a = acos(-1);
	norm.teta_b = acos(1);
	if (norm.teta < norm.teta_a && norm.teta > norm.teta_b &&
			norm.z < norm.zb && norm.z > norm.za)
	{
		*col = ft_get_tex_color((int)((norm.teta - norm.teta_a) / (norm.teta_b -
norm.teta_a) * cur_obj->mat.tex.width1), (int)(cur_obj->mat.tex.height1 - (((
norm.z - norm.za) / (norm.zb - norm.za)) * cur_obj->mat.tex.height1)), cur_obj);
		return (1);
	}
	return (0);
}

unsigned int	ft_texture_sphere(t_ray *ray, double t, t_obj *cur_obj,
		t_color *col)
{
	float	s;

	s = (acos((ray->dir.y * t + ray->pos.y - cur_obj->pos.y) /
				cur_obj->rayon) / M_PI);
	*col = ft_get_tex_color((int)(s * cur_obj->mat.tex.height1),
		(int)((acos((ray->dir.x * t + ray->pos.x - cur_obj->pos.x)
			/ (cur_obj->rayon * sin(M_PI * s))) / (2 * M_PI)) *
				cur_obj->mat.tex.width1), cur_obj);
	return (1);
}
