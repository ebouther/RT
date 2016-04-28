/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:31:25 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/28 14:06:17 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

double			inters_sphere(t_ray *ray, t_obj *obj, int k)
{
	double a;
	double b;
	double c;

	a = carre(ray->dir.x) + carre(ray->dir.y) + carre(ray->dir.z);
	b = 2 * (ray->dir.x * (ray->pos.x - obj->pos.x) +
			ray->dir.y * (ray->pos.y - obj->pos.y) +
			ray->dir.z * (ray->pos.z - obj->pos.z));
	c = (carre(ray->pos.x - obj->pos.x) +
			carre(ray->pos.y - obj->pos.y) +
			carre(ray->pos.z - obj->pos.z)) - carre(obj->rayon);
	if (k)
		printf("a = %f, b= %f, c = %f\n",a,b,c);
	return (ft_equa_sec(a, b, c));
	k=0;
}

double			inters_plan(t_ray *ray, t_obj *obj, int k)
{
	double	vd;
	double	t;

	vd = obj->norm.x * ray->dir.x +
		obj->norm.y * ray->dir.y +
		obj->norm.z * ray->dir.z;
	if (vd == 0)
		return (FAR);
	t = (obj->norm.x * (obj->pos.x - ray->pos.x) +
			obj->norm.y * (obj->pos.y - ray->pos.y) +
			obj->norm.z * (obj->pos.z - ray->pos.z)) / vd;
	if (t >= 0)
		return (t);
	else
		return (FAR);
	k=0;
}

double			inters_cyl(t_ray *ray, t_obj *obj, int k)
{
	double	a[6];
	double	b[3];
	double	c[3];
	double	d[3];

	a[0] = ray->dir.x;
	a[1] = ray->dir.y;
	a[2] = ray->dir.z;
	a[3] = ray->pos.x - obj->pos.x;
	a[4] = ray->pos.y - obj->pos.y;
	a[5] = ray->pos.z - obj->pos.z;
	b[0] = a[4] * obj->dir.z - a[5] * obj->dir.y;
	b[1] = a[3] * obj->dir.z - a[5] * obj->dir.x;
	b[2] = a[3] * obj->dir.y - a[4] * obj->dir.x;
	c[0] = a[1] * obj->dir.z - a[2] * obj->dir.y;
	c[1] = a[0] * obj->dir.z - a[2] * obj->dir.x;
	c[2] = a[0] * obj->dir.y - a[1] * obj->dir.x;
	d[0] = carre(c[0]) + carre(c[1]) + carre(c[2]);
	d[1] = 2 * (b[0] * c[0] + b[1] * c[1] + b[2] * c[2]);
	d[2] = carre(b[0]) + carre(b[1]) + carre(b[2]) - carre(obj->rayon);
	return (ft_equa_sec(d[0], d[1], d[2]));
	k=0;
}

double			inters_cone(t_ray *ray, t_obj *obj, int k)
{
	double	a[6];
	double	b[2];
	double	c[3];

	a[0] = ray->dir.x;
	a[1] = ray->dir.y;
	a[2] = ray->dir.z;
	a[3] = ray->pos.x - obj->pos.x;
	a[4] = ray->pos.y - obj->pos.y;
	a[5] = ray->pos.z - obj->pos.z;
	b[0] = a[0] * obj->dir.x + a[1] * obj->dir.y + a[2] * obj->dir.z;
	b[1] = obj->dir.x * a[3] + obj->dir.y * a[4] + obj->dir.z * a[5];
	c[0] = carre(cos(obj->angle)) * (carre(a[0]) + carre(a[1]) + carre(a[2])) - carre(b[0]);
	c[1] = 2 * carre(cos(obj->angle)) * (a[0] * a[3] + a[1] * a[4] + a[2] * a[5]) - 2 * b[0] * b[1];
	c[2] = carre(cos(obj->angle)) *	(carre(a[3]) + carre(a[4]) + carre(a[5])) - carre(b[1]);
	return (ft_equa_sec(c[0], c[1], c[2]));
	k=0;
}
