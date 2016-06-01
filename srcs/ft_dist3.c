/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:41:50 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 17:57:35 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	*inters_sphere2(t_ray *ray, t_obj *obj)
{
	double	a;
	double	b;
	double	c;
	double	*res;

	a = carre(ray->dir.x) + carre(ray->dir.y) + carre(ray->dir.z);
	b = 2 * (ray->dir.x * (ray->pos.x - obj->pos.x) +
			ray->dir.y * (ray->pos.y - obj->pos.y) +
			ray->dir.z * (ray->pos.z - obj->pos.z));
	c = (carre(ray->pos.x - obj->pos.x) +
			carre(ray->pos.y - obj->pos.y) +
			carre(ray->pos.z - obj->pos.z)) - carre(obj->rayon);
	res = ft_equa_sec2(a, b, c);
	return (res);
}

static double	ft_equ(double t, t_ray *ray, t_obj *obj)
{
	t_vec3 cb;
	t_vec3 tmp;

	tmp = (t_vec3){obj->pos.x, obj->pos.y, obj->pos.z};
	ft_rot_vec(obj->rot.x, (t_vec3){1, 0, 0}, &(tmp));
	ft_rot_vec(obj->rot.y, (t_vec3){0, 1, 0}, &(tmp));
	ft_rot_vec(obj->rot.z, (t_vec3){0, 0, 1}, &(tmp));
	cb.x = t * ray->dir.x + ray->pos.x;
	cb.y = t * ray->dir.y + ray->pos.y;
	cb.z = t * ray->dir.z + ray->pos.z;
	return (cb.x * obj->equ.x1 + carre(cb.x) * obj->equ.x2 + cb.y
		* obj->equ.y1 + carre(cb.y) * obj->equ.y2 + cb.z * obj->equ.z1
		+ carre(cb.z) * obj->equ.z2 + obj->equ.c);
}

static double	ft_rec(double t1, double t2, t_ray *ray, t_obj *obj, int s)
{
	if (fabs(t1 - t2) < 0.001)
		return (fmin(t1, t2));
	if (ft_equ((t1 + t2) / 2.0, ray, obj) > 0 && s)
		return (ft_rec((t1 + t2) / 2.0, t2, ray, obj, s));
	else
		return (ft_rec(t1, (t1 + t2) / 2.0, ray, obj, s));
}

static double	*ft_init_inters(t_obj *obj, t_ray *tmp, t_ray *ray, double **t)
{
	double	*res;

	*tmp = (t_ray){{ray->pos.x - obj->pos.x, ray->pos.y - obj->pos.y,
		ray->pos.z - obj->pos.z}, {ray->dir.x, ray->dir.y, ray->dir.z}, 0, 0};
	ft_rot_vec(obj->rot.x, (t_vec3){1, 0, 0}, &(tmp->pos));
	ft_rot_vec(obj->rot.x, (t_vec3){1, 0, 0}, &(tmp->dir));
	ft_rot_vec(obj->rot.y, (t_vec3){0, 1, 0}, &(tmp->pos));
	ft_rot_vec(obj->rot.y, (t_vec3){0, 1, 0}, &(tmp->dir));
	ft_rot_vec(obj->rot.z, (t_vec3){0, 0, 1}, &(tmp->pos));
	ft_rot_vec(obj->rot.z, (t_vec3){0, 0, 1}, &(tmp->dir));
	*t = inters_sphere2(ray, obj);
	res = (double*)malloc(sizeof(double) * 2);
	res[1] = FAR;
	res[0] = FAR;
	if ((*t)[0] == FAR || ((*t)[0] < 0 && (*t)[1] < 0))
		res[0] = FAR;
	return (res);
}

double			*inters_quadra(t_ray *ray, t_obj *obj)
{
	double	*t;
	double	t1;
	double	r[2];
	double	*res;
	t_ray	tmp;

	t = NULL;
	res = ft_init_inters(obj, &tmp, ray, &t);
	t1 = (t[0] < 0) ? -0.1 : t[0] - 0.1;
	while (t1 < t[1] && (t1 = t1 + 0.1) > -1)
	{
		r[1] = ft_equ(t1 + 0.1, &tmp, obj);
		r[0] = ft_equ(t1, &tmp, obj);
		if (r[0] == 0.0)
		{
			res[0] = t1;
			break ;
		}
		else if ((r[1] * r[0]) < 0.0)
		{
			res[0] = ft_rec(t1, t1 + 0.1, &tmp, obj, r[0] > 0);
			break ;
		}
	}
	return (res);
}
