/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_contact2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 09:45:01 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 12:00:25 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_vec3	*normal_cube(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;
	t_vec3	tmp;

	tmp.x = ray->pos.x - obj->pos.x;
	tmp.y = ray->pos.y - obj->pos.y;
	tmp.z = ray->pos.z - obj->pos.z;
	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	if (fabs(fabs(scal(tmp, obj->dir)) - obj->scale.z / 2.0) < 0.01)
	{
		res->x = obj->dir.x;
		res->y = obj->dir.y;
		res->z = obj->dir.z;
	}
	else if (fabs(fabs(scal(tmp, obj->dir2)) - obj->scale.y / 2.0) < 0.01)
	{
		res->x = obj->dir2.x;
		res->y = obj->dir2.y;
		res->z = obj->dir2.z;
	}
	else if (fabs(fabs(scal(tmp, obj->dir3)) - obj->scale.x / 2.0) < 0.01)
	{
		res->x = obj->dir3.x;
		res->y = obj->dir3.y;
		res->z = obj->dir3.z;
	}
	else
	{
		res->x = 0;
		res->y = 0;
		res->z = 0;
	}
	ft_normalise(res);
	return (scal(*res, tmp) >= 0 ? res : pro(-1, res));
}

t_vec3	*normal_tore(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;
	t_vec3	cb;
	t_vec3	ch;
	double	p;

	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	cb.x = ray->pos.x - obj->pos.x;
	cb.y = ray->pos.y - obj->pos.y;
	cb.z = ray->pos.z - obj->pos.z;
	p = cb.x * obj->dir.x + cb.y * obj->dir.y + cb.z * obj->dir.z;
	ch.x = cb.x - obj->dir.x * p;
	ch.y = cb.y - obj->dir.y * p;
	ch.z = cb.z - obj->dir.z * p;
	ft_normalise(&ch);
	res->x = ray->pos.x - obj->pos.x - ch.x * obj->rayon;
	res->y = ray->pos.y - obj->pos.y - ch.y * obj->rayon;
	res->z = ray->pos.z - obj->pos.z - ch.z * obj->rayon;
	ft_normalise(res);
	if (kk)
		printf("tore normal : (%f, %f, %f)\n",res->x,res->y, res->z);
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}

t_vec3	*normal_pobj(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;

	(void)ray;
	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	*res = (t_vec3){obj->norm.x, obj->norm.y, obj->norm.z};
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}

t_vec3	*normal_quadra(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;
	t_vec3	pp;

	if ((res = (t_vec3 *)malloc(sizeof(t_vec3))) == NULL)
		exit(-1);
	pp = (t_vec3){ray->pos.x - obj->pos.x, ray->pos.y - obj->pos.y,
		ray->pos.z - obj->pos.z};
	ft_rot_vec(obj->rot.x, (t_vec3){1, 0, 0}, &pp);
	ft_rot_vec(obj->rot.y, (t_vec3){0, 1, 0}, &pp);
	ft_rot_vec(obj->rot.z, (t_vec3){0, 0, 1}, &pp);
	res->x = pp.x * 2 * obj->equ.x2 + obj->equ.x1;
	res->y = pp.y * 2 * obj->equ.y2 + obj->equ.y1;
	res->z = pp.z * 2 * obj->equ.z2 + obj->equ.z1;
	ft_rot_vec(-obj->rot.x, (t_vec3){1, 0, 0}, res);
	ft_rot_vec(-obj->rot.y, (t_vec3){0, 1, 0}, res);
	ft_rot_vec(-obj->rot.z, (t_vec3){0, 0, 1}, res);
	ft_normalise(res);
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}
