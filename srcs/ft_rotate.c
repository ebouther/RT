/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 11:15:13 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/25 11:15:44 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec3	ft_rotate_x(t_vec3 v, t_vec3 center, t_vec3 rot)
{
	t_vec3	vt;
	t_vec3	res;

	vt = v;
	vt = (t_vec3){v.x - center.x, v.y - center.y, v.z - center.z};
	res.x = v.x;
	res.y = (vt.y * cos(rot.x * (M_PI / 180)))
			+ (vt.z * sin(rot.x * (M_PI / 180)));
	res.z = (vt.y * -sin(rot.x * (M_PI / 180)))
			+ (vt.z * cos(rot.x * (M_PI / 180)));
	res = (t_vec3){res.x + center.x, res.y + center.y, res.z + center.z};
	return (res);
}

static t_vec3	ft_rotate_y(t_vec3 v, t_vec3 center, t_vec3 rot)
{
	t_vec3	vt;
	t_vec3	res;

	vt = v;
	vt = (t_vec3){v.x - center.x, v.y - center.y, v.z - center.z};
	res.x = (vt.x * cos(rot.y * (M_PI / 180)))
			+ (vt.z * -sin(rot.y * (M_PI / 180)));
	res.y = v.y;
	res.z = (vt.x * sin(rot.y * (M_PI / 180)))
			+ (vt.z * cos(rot.y * (M_PI / 180)));
	res = (t_vec3){res.x + center.x, res.y + center.y, v.z + center.z};
	return (res);
}

static t_vec3	ft_rotate_z(t_vec3 v, t_vec3 center, t_vec3 rot)
{
	t_vec3	vt;
	t_vec3	res;

	vt = v;
	vt = (t_vec3){v.x - center.x, v.y - center.y, v.z - center.z};
	res.x = (vt.x * cos(rot.z * (M_PI / 180)))
			+ (vt.y * sin(rot.z * (M_PI / 180)));
	res.y = (vt.x * -sin(rot.z * (M_PI / 180)))
			+ (vt.y * cos(rot.z * (M_PI / 180)));
	res.z = v.z;
	res = (t_vec3){res.x + center.x, res.y + center.y, v.z + center.z};
	return (res);
}

t_vec3			ft_rotate(t_vec3 v, t_vec3 center, t_vec3 rot)
{
	t_vec3	res;

	res = ft_rotate_x(v, center, rot);
	res = ft_rotate_y(res, center, rot);
	res = ft_rotate_z(res, center, rot);
	return (res);
}
