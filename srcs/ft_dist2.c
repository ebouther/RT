/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 09:38:57 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/24 14:26:59 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

double		*ft_equa_sec2(double a, double b, double c)
{
	double delt;
	double r1;
	double r2;
	double *res;

	res = (double*)malloc(sizeof(double) * 2);
	delt = carre(b) - 4 * a * c;
	if (delt < 0)
	{
		res[0] = FAR;
		res[1] = FAR;
	}
	else if (delt > 0)
	{
		r1 = (-b - sqrt(delt)) / (2 * a);
		r2 = (-b + sqrt(delt)) / (2 * a);
		res[0] = fmin(r1, r2);
		res[1] = fmax(r1, r2);
	}
	else
	{
		res[0] = (-b / (2 * a));
		res[1] = (-b / (2 * a));
	}
	return (res);
}

static double			*inters_sphere2(t_ray *ray, t_obj *obj)
{
	double a;
	double b;
	double c;
	double	*res;

	a = carre(ray->dir.x) + carre(ray->dir.y) + carre(ray->dir.z);
	b = 2 * (ray->dir.x * (ray->pos.x - obj->pos.x) +
			ray->dir.y * (ray->pos.y - obj->pos.y) +
			ray->dir.z * (ray->pos.z - obj->pos.z));
	c = (carre(ray->pos.x - obj->pos.x) +
			carre(ray->pos.y - obj->pos.y) +
			carre(ray->pos.z - obj->pos.z)) - carre(obj->rayon + obj->rayon2);
	res = ft_equa_sec2(a, b, c);
	return (res);
}

static double	ft_tor(double t, t_ray *ray, t_obj *obj)
{
	t_vec3 cb;
	double r;
	double R;

	cb.x = t * ray->dir.x + ray->pos.x - obj->pos.x;
	cb.y = t * ray->dir.y + ray->pos.y - obj->pos.y;
	cb.z = t * ray->dir.z + ray->pos.z - obj->pos.z;
	r = obj->rayon2;
	R = obj->rayon;
	return (carre(scal2(cb) - carre(r) + carre(R)) - 4 * carre(R) * (scal2(cb) - carre(scal(cb, obj->dir))));
}

static double	ft_rec(double r1, double r2, t_ray *ray, t_obj *obj)
{
	if (fabs(r1 - r2) < 0.0001)
		return (r1);
	if (ft_tor((r1 + r2) / 2.0, ray, obj) > 0)
		return (ft_rec((r1 + r2) / 2.0, r2, ray, obj));
	else
		return (ft_rec(r1, (r1 + r2) / 2.0, ray, obj));
}

double	*inters_tore(t_ray *ray, t_obj *obj)
{
	double *t;
	double r1;
	double r2;
	double *res;

	res = (double*)malloc(sizeof(double) * 2);
	t = inters_sphere2(ray, obj);
	res[1] = FAR;
	res[0] = FAR;
	if (t[0] == FAR || (t[0] < 0 && t[1] < 0))
		res[0] = FAR;
	if (t[0] < 0)
		r1 = 0;
	else	
		r1 = t[0];
	while (r1 < t[1])
	{
		r2 = ft_tor(r1, ray, obj);
		if (r2 == 0)
		{
			res[0] = r1;
			return (res);
		}
		else if (r2 < 0)
		{
			res[0] = ft_rec(r1 - 0.1, r1, ray, obj);
			return (res);
		}
		r1 += 0.1;
	}
	return (res);
}
