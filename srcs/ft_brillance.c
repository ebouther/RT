/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brillance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:03:54 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/11 14:16:35 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	ft_bri_sph(int i, t_env *e)
{
	double n[3];
	double r[3];
	double p;

	n[0] = e->ray.orix - e->obj[i].centrex;
	n[1] = e->ray.oriy - e->obj[i].centrey;
	n[2] = e->ray.oriz - e->obj[i].centrez;
	ft_normalise(&n[0], &n[1], &n[2]);
	p = n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z;
	r[0] = -e->ray.x + 2 * n[0] * p;
	r[1] = -e->ray.y + 2 * n[1] * p;
	r[2] = -e->ray.z + 2 * n[2] * p;
	ft_normalise(&r[0], &r[1], &r[2]);
	return (r[0] * e->ray.oeilx + r[1] * e->ray.oeily + r[2] * e->ray.oeilz);
}

static double	ft_bri_plan(int i, t_env *e)
{
	double n[3];
	double r[3];
	double p;

	n[0] = e->obj[i].normalx;
	n[1] = e->obj[i].normaly;
	n[2] = e->obj[i].normalz;
	p = n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z;
	r[0] = -e->ray.x + 2 * n[0] * p;
	r[1] = -e->ray.y + 2 * n[1] * p;
	r[2] = -e->ray.z + 2 * n[2] * p;
	ft_normalise(&r[0], &r[1], &r[2]);
	return (r[0] * e->ray.oeilx + r[1] * e->ray.oeily + r[2] * e->ray.oeilz);
}

static double	ft_bri_cyl(int i, t_env *e)
{
	double n[3];
	double r[3];
	double p[2];

	p[0] = e->obj[i].directx * (e->ray.orix - e->obj[i].centrex) +
		e->obj[i].directy * (e->ray.oriy - e->obj[i].centrey) +
		e->obj[i].directz * (e->ray.oriz - e->obj[i].centrez);
	n[0] = e->ray.orix - e->obj[i].centrex - e->obj[i].directx * p[0];
	n[1] = e->ray.oriy - e->obj[i].centrey - e->obj[i].directy * p[0];
	n[2] = e->ray.oriz - e->obj[i].centrez - e->obj[i].directz * p[0];
	ft_normalise(&n[0], &n[1], &n[2]);
	p[1] = n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z;
	r[0] = -e->ray.x + 2 * n[0] * p[1];
	r[1] = -e->ray.y + 2 * n[1] * p[1];
	r[2] = -e->ray.z + 2 * n[2] * p[1];
	ft_normalise(&r[0], &r[1], &r[2]);
	return (r[0] * e->ray.oeilx + r[1] * e->ray.oeily + r[2] * e->ray.oeilz);
}

static double	ft_bri_cone(int i, t_env *e)
{
	double n[3];
	double r[3];
	double p[3];

	p[0] = e->obj[i].directx * (e->ray.orix - e->obj[i].centrex) +
		e->obj[i].directy * (e->ray.oriy - e->obj[i].centrey) +
		e->obj[i].directz * (e->ray.oriz - e->obj[i].centrez);
	n[0] = e->ray.orix - e->obj[i].centrex - e->obj[i].directx * p[0];
	n[1] = e->ray.oriy - e->obj[i].centrey - e->obj[i].directy * p[0];
	n[2] = e->ray.oriz - e->obj[i].centrez - e->obj[i].directz * p[0];
	p[2] = ft_norm(n[0], n[1], n[2]);
	n[0] = n[0] * cos(e->obj[i].angle) - p[2] * e->obj[i].directx
		* sin(e->obj[i].angle) * p[0] / fabs(p[0]);
	n[1] = n[1] * cos(e->obj[i].angle) - p[2] * e->obj[i].directy
		* sin(e->obj[i].angle) * p[0] / fabs(p[0]);
	n[2] = n[2] * cos(e->obj[i].angle) - p[2] * e->obj[i].directz
		* sin(e->obj[i].angle) * p[0] / fabs(p[0]);
	ft_normalise(&n[0], &n[1], &n[2]);
	p[1] = n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z;
	r[0] = -e->ray.x + 2 * n[0] * p[1];
	r[1] = -e->ray.y + 2 * n[1] * p[1];
	r[2] = -e->ray.z + 2 * n[2] * p[1];
	ft_normalise(&r[0], &r[1], &r[2]);
	return (r[0] * e->ray.oeilx + r[1] * e->ray.oeily + r[2] * e->ray.oeilz);
}

double			ft_brillance(t_env *e, int i)
{
	double s;

	if (e->obj[i].type.sph)
		s = ft_bri_sph(i, e);
	else if (e->obj[i].type.plan)
		s = ft_bri_plan(i, e);
	else if (e->obj[i].type.cyl)
		s = ft_bri_cyl(i, e);
	else
		s = ft_bri_cone(i, e);
	if (s <= 0)
		return (0);
	else
		return (s);
}
