/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 14:34:14 by pboutin           #+#    #+#             */
/*   Updated: 2016/05/25 11:11:16 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			ft_get_tex_color(int x, int y, t_obj *cur_obj)
{
	unsigned char	*c;
	t_color			ret;

	c = (unsigned char*)cur_obj->mat.tex.buf
		+ (x) * 4 + (y * cur_obj->mat.tex.width1 * 4);
	ret.b = *c / 256.0;
	ret.g = *(c + 1) / 256.0;
	ret.r = *(c + 2) / 256.0;
	return (ret);
}

void			ft_rot_axex(double angle, t_vec3 *vec)
{
	double	y;

	y = vec->y;
	vec->y = vec->y * cos(angle) - vec->z * sin(angle);
	vec->z = y * sin(angle) + vec->z * cos(angle);
}

void			ft_rot_axez(double angle, t_vec3 *vec)
{
	double	x;

	x = vec->x;
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = x * sin(angle) + vec->y * cos(angle);
}

t_vec3			ft_norm_tex(t_ray *ray, double t, t_obj *cur_obj, int i)
{
	t_vec3	pos;

	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	if (i == -18000)
		pos.y = ray->dir.y * t + ray->pos.y - cur_obj->pos.y;
	else
		pos.y = i;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	return (pos);
}

void			ft_norm_tex_rot(t_obj *cur_obj, t_vec3 *pos)
{
	ft_rot_axez(asin(cur_obj->dir.x), pos);
	ft_rot_axex(asin(cur_obj->dir.z), pos);
}
