/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_contact.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:02:02 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/11 14:10:22 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	ft_angle_sph(int i, t_env *e)
{
	double n[3];

	n[0] = e->ray.orix - e->obj[i].centrex;
	n[1] = e->ray.oriy - e->obj[i].centrey;
	n[2] = e->ray.oriz - e->obj[i].centrez;
	ft_normalise(&n[0], &n[1], &n[2]);
	return (n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z);
}

static double	ft_angle_cyl(int i, t_env *e)
{
	double n[3];
	double p;

	p = e->obj[i].directx * (e->ray.orix - e->obj[i].centrex) +
		e->obj[i].directy * (e->ray.oriy - e->obj[i].centrey) +
		e->obj[i].directz * (e->ray.oriz - e->obj[i].centrez);
	n[0] = e->ray.orix - e->obj[i].centrex - e->obj[i].directx * p;
	n[1] = e->ray.oriy - e->obj[i].centrey - e->obj[i].directy * p;
	n[2] = e->ray.oriz - e->obj[i].centrez - e->obj[i].directz * p;
	ft_normalise(&n[0], &n[1], &n[2]);
	return (n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z);
}

static double	ft_angle_cone(int i, t_env *e)
{
	double n[3];
	double p;
	double norm;

	p = e->obj[i].directx * (e->ray.orix - e->obj[i].centrex) +
		e->obj[i].directy * (e->ray.oriy - e->obj[i].centrey) +
		e->obj[i].directz * (e->ray.oriz - e->obj[i].centrez);
	n[0] = e->ray.orix - e->obj[i].centrex - e->obj[i].directx * p;
	n[1] = e->ray.oriy - e->obj[i].centrey - e->obj[i].directy * p;
	n[2] = e->ray.oriz - e->obj[i].centrez - e->obj[i].directz * p;
	norm = ft_norm(n[0], n[1], n[2]);
	n[0] = n[0] * cos(e->obj[i].angle) - norm *
		e->obj[i].directx * sin(e->obj[i].angle) * p / fabs(p);
	n[1] = n[1] * cos(e->obj[i].angle) - norm *
		e->obj[i].directy * sin(e->obj[i].angle) * p / fabs(p);
	n[2] = n[2] * cos(e->obj[i].angle) - norm *
		e->obj[i].directz * sin(e->obj[i].angle) * p / fabs(p);
	ft_normalise(&n[0], &n[1], &n[2]);
	return (n[0] * e->ray.x + n[1] * e->ray.y + n[2] * e->ray.z);
}

double			ft_angle_contact(t_env *e, int i)
{
	double s;

	if (e->obj[i].type.sph)
		s = ft_angle_sph(i, e);
	else if (e->obj[i].type.plan)
		s = e->obj[i].normalx * e->ray.x +
			e->obj[i].normaly * e->ray.y + e->obj[i].normalz * e->ray.z;
	else if (e->obj[i].type.cyl)
		s = ft_angle_cyl(i, e);
	else
		s = ft_angle_cone(i, e);
	if (s >= 0 & s <= 1)
		return (s);
	else
		return (0);
}
