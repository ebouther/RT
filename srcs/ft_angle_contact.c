/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_contact.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:02:02 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 21:30:18 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	*ft_normal_sphere(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;

	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	res->x = ray->pos.x - obj->pos.x;
	res->y = ray->pos.y - obj->pos.y;
	res->z = ray->pos.z - obj->pos.z;
	ft_normalise(res);
	return (res);
}

t_vec3	*ft_normal_cyl(t_ray *ray, t_obj *obj)
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
	return (res);
}

t_vec3	*ft_normal_cone(t_ray *ray, t_obj *obj)
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
	res->x = res->x * cos(obj->angle) - norm *
		obj->dir.x * sin(obj->angle) * p / fabs(p);
	res->y = res->y * cos(obj->angle) - norm *
		obj->dir.y * sin(obj->angle) * p / fabs(p);
	res->z = res->z * cos(obj->angle) - norm *
		obj->dir.z * sin(obj->angle) * p / fabs(p);
	ft_normalise(res);
	return (res);
}

t_vec3	*ft_normal_plan(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;

	(void *)ray;
	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	*res = (t_vec3){obj->norm.x, obj->norm.y, obj->norm.z};
	return (res);
}

double			ft_angle_contact(t_ray *ray, t_vec3 *normal)
{
	double s;

	s = normal->dir.x * ray->dir.x +
		normal->dir.y * ray->dir.y + normal->dir.z * ray->dir.z;
	if (s >= 0 & s <= 1)
		return (s);
	return (0);
}
