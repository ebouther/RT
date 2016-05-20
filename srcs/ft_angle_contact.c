/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_contact.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:02:02 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/20 18:04:40 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

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

static t_vec3	ft_rotate(t_vec3 v, t_vec3 center, t_vec3 rot)
{
	t_vec3	res;

	res = ft_rotate_x(v, center, rot);
	res = ft_rotate_y(res, center, rot);
	res = ft_rotate_z(res, center, rot);
	return (res);
}

t_vec3	*normal_sphere(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;

	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	res->x = ray->pos.x - obj->pos.x;
	res->y = ray->pos.y - obj->pos.y;
	res->z = ray->pos.z - obj->pos.z;
	ft_normalise(res);
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}

t_vec3	*normal_cyl(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;
	double p;
	
	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	p = obj->dir.x * (ray->pos.x - obj->pos.x) +
		obj->dir.y * (ray->pos.y - obj->pos.y) +
		obj->dir.z * (ray->pos.z - obj->pos.z);
	res->x = ray->pos.x - obj->pos.x - obj->dir.x * p;
	res->y = ray->pos.y - obj->pos.y - obj->dir.y * p;
	res->z = ray->pos.z - obj->pos.z - obj->dir.z * p;
	ft_normalise(res);
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}

t_vec3	*normal_cone(t_ray *ray, t_obj *obj)
{
	double	p;
	double	norm;
	t_vec3	*res;

	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	p = obj->dir.x * (ray->pos.x - obj->pos.x) +
		obj->dir.y * (ray->pos.y - obj->pos.y) +
		obj->dir.z * (ray->pos.z - obj->pos.z);
	res->x = ray->pos.x - obj->pos.x - obj->dir.x * p;
	res->y = ray->pos.y - obj->pos.y - obj->dir.y * p;
	res->z = ray->pos.z - obj->pos.z - obj->dir.z * p;
	norm = ft_norm(res);
	res->x = res->x * cos(obj->angle) - norm * obj->dir.x * sin(obj->angle) * p / fabs(p);
	res->y = res->y * cos(obj->angle) - norm * obj->dir.y * sin(obj->angle) * p / fabs(p);
	res->z = res->z * cos(obj->angle) - norm * obj->dir.z * sin(obj->angle) * p / fabs(p);
	ft_normalise(res);
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}

t_vec3	*normal_plan(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;

	(void)ray;
	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	*res = (t_vec3){obj->norm.x, obj->norm.y, obj->norm.z};
	if (obj->mat.waves == TRUE)
		*res = ft_rotate(*res, (t_vec3){0, 0, 0}, (t_vec3){sin(ray->pos.y), sin(ray->pos.x), sin(ray->pos.z)});
	ft_normalise(res);
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}

double			ft_angle_contact(t_ray *ray, t_vec3 *normal)
{
	double s;

	s = normal->x * ray->dir.x +
		normal->y * ray->dir.y + normal->z * ray->dir.z;
	if (kk)
		printf("scal angle = %f\n",s);
	if (s >= 0 && s <= 1)
		return (s);
	return (0);
}
