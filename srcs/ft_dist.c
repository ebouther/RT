/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:31:25 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/20 15:04:16 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			ft_dist_sphere(int i, t_env *e)
{
	double a;
	double b;
	double c;

	a = carre(e->ray.x) + carre(e->ray.y) + carre(e->ray.z);
	b = 2 * (e->ray.x * (e->ray.orix - e->obj[i].centrex) +
			e->ray.y * (e->ray.oriy - e->obj[i].centrey) +
			e->ray.z * (e->ray.oriz - e->obj[i].centrez));
	c = (carre(e->ray.orix - e->obj[i].centrex) +
			carre(e->ray.oriy - e->obj[i].centrey) +
			carre(e->ray.oriz - e->obj[i].centrez)) - carre(e->obj[i].rayon);
	return (ft_equa_sec(a, b, c));
}

double			ft_dist_plan(int i, t_env *e)
{
	double	vd;
	double	t;

	vd = e->obj[i].normalx * e->ray.x +
		e->obj[i].normaly * e->ray.y +
		e->obj[i].normalz * e->ray.z;
	if (vd == 0)
		return (1000000000);
	t = (e->obj[i].normalx * (e->obj[i].centrex - e->ray.orix) +
			e->obj[i].normaly * (e->obj[i].centrey - e->ray.oriy) +
			e->obj[i].normalz * (e->obj[i].centrez - e->ray.oriz)) / vd;
	if (t >= 0)
		return (t);
	else
		return (1000000000);
}

double			ft_dist_cyl(int i, t_env *e)
{
	double	a[6];
	double	b[3];
	double	c[3];
	double	d[3];

	a[0] = e->ray.x;
	a[1] = e->ray.y;
	a[2] = e->ray.z;
	a[3] = e->ray.orix - e->obj[i].centrex;
	a[4] = e->ray.oriy - e->obj[i].centrey;
	a[5] = e->ray.oriz - e->obj[i].centrez;
	b[0] = a[4] * e->obj[i].directz - a[5] * e->obj[i].directy;
	b[1] = a[3] * e->obj[i].directz - a[5] * e->obj[i].directx;
	b[2] = a[3] * e->obj[i].directy - a[4] * e->obj[i].directx;
	c[0] = a[1] * e->obj[i].directz - a[2] * e->obj[i].directy;
	c[1] = a[0] * e->obj[i].directz - a[2] * e->obj[i].directx;
	c[2] = a[0] * e->obj[i].directy - a[1] * e->obj[i].directx;
	d[0] = carre(c[0]) + carre(c[1]) + carre(c[2]);
	d[1] = 2 * (b[0] * c[0] + b[1] * c[1] + b[2] * c[2]);
	d[2] = carre(b[0]) + carre(b[1]) + carre(b[2]) - carre(e->obj[i].rayon);
	return (ft_equa_sec(d[0], d[1], d[2]));
}

double			ft_dist_cone(int i, t_env *e)
{
	double	a[6];
	double	b[2];
	double	c[3];

	a[0] = e->ray.x;
	a[1] = e->ray.y;
	a[2] = e->ray.z;
	a[3] = e->ray.orix - e->obj[i].centrex;
	a[4] = e->ray.oriy - e->obj[i].centrey;
	a[5] = e->ray.oriz - e->obj[i].centrez;
	b[0] = a[0] * e->obj[i].directx + a[1] * e->obj[i].directy
		+ a[2] * e->obj[i].directz;
	b[1] = e->obj[i].directx * a[3] + e->obj[i].directy * a[4]
		+ e->obj[i].directz * a[5];
	c[0] = carre(cos(e->obj[i].angle)) * (carre(a[0]) + carre(a[1]) +
			carre(a[2])) - carre(b[0]);
	c[1] = 2 * carre(cos(e->obj[i].angle)) *
		(a[0] * a[3] + a[1] * a[4] + a[2] * a[5]) - 2 * b[0] * b[1];
	c[2] = carre(cos(e->obj[i].angle)) *
		(carre(a[3]) + carre(a[4]) + carre(a[5])) - carre(b[1]);
	return (ft_equa_sec(c[0], c[1], c[2]));
}

double			ft_dist(int i, t_env *e)
{
	if (e->obj[i].type.sph)
		return (ft_dist_sphere(i, e));
	else if (e->obj[i].type.plan)
		return (ft_dist_plan(i, e));
	else if (e->obj[i].type.cyl)
		return (ft_dist_cyl(i, e));
	else if (e->obj[i].type.cone)
		return (ft_dist_cone(i, e));
	return (0);
}
