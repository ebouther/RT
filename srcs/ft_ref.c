/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ref.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 15:43:31 by ascholle          #+#    #+#             */
/*   Updated: 2016/04/27 17:40:13 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		*ft_refr(t_ray *ray, t_work *work, double *refl)
{
	double	al1;
	double	n;
	double	p;
	t_ray	*ray;
	double	calc;

	p = scal(ray->dir, work->normal);
	al1 = sin(acos(-scal(work->normal, ray->dir)));
	if (ray->i_opt * work->obj->mat.i_opt )
	{
		*refl = work->obj.mat.refr;
		return (NULL);
	}
	if ((res = (t_ray*)malloc(sizeof(t_ray))) == NULL)
		exit(-1);
	n = ray->i_opt / work->obj->mat.i_opt;
	calc = n * p - sqrt(1 + carre(n) * (carre(p) - 1));
	res->dir.x = n * ray->dir.x + calc * work->normal.x;
	res->dir.y = n * ray->dir.y + calc * work->normal.y;
	res->dir.x = n * ray->dir.z + calc * work->normal.z;
	ft_normalise(&res->dir);
	res->pos.x = work->ray->pos.x;
	res->pos.y = work->ray->pos.y;
	res->pos.z = work->ray->pos.z;
	res->i_opt = work->obj->mat.i_opt;
	res->iter = ray->iter + 1;
	return (res);
}

t_ray		*ft_refl(t_ray *ray, t_work *work)
{
	t_ray	*res;
	double	p;

	if ((res = (t_ray*)malloc(sizeof(t_ray))) == NULL)
		exit(-1);
	p = work->normal->x * -ray->dir.x + work->normal->y * -ray->dir.y + work->normal->z * -ray->dir.z;
	res->dir.x = ray->dir.x + 2 * work->normal.x * p;
	res->dir.y = ray->dir.y + 2 * work->normal.y * p;
	res->dir.z = ray->dir.z + 2 * work->normal.z * p;
	ft_normalise(&ray->dir);
	res->pos.x = work->ray->pos.x;
	res->pos.y = work->ray->pos.y;
	res->pos.z = work->ray->pos.z;
	res->i_opt = ray->i_opt;
	res->iter = ray->iter + 1;
	return (res);
}
