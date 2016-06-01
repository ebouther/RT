/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 09:57:59 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 17:51:40 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static int ft_incube(double t, t_ray* ray,t_obj* obj)
{
	t_vec3 tmp;

	tmp.x = (ray->pos.x + t * ray->dir.x - obj->pos.x);
	tmp.y = (ray->pos.y + t * ray->dir.y - obj->pos.y);
	tmp.z = (ray->pos.z + t * ray->dir.z - obj->pos.z);

	if (fabs(scal(tmp, obj->dir)) - 0.0001 <= fabs(obj->scale.z / 2.0) &&
			fabs(scal(tmp, obj->dir2)) - 0.0001 <= fabs(obj->scale.y / 2.0) &&
			fabs(scal(tmp, obj->dir3)) - 0.0001 <= fabs(obj->scale.x / 2.0))
		return (1);
	return (0);
}

double			*inters_cube(t_ray *ray, t_obj *obj)
{
	t_vec3	p;
	double	*res;
	double tmp;
	double	a;
	double	b;

	p.x = ray->pos.x - obj->pos.x;
	p.y = ray->pos.y - obj->pos.y;
	p.z = ray->pos.z - obj->pos.z;
	if ((res = (double*)malloc(sizeof(double) * 2)) == NULL)
		ft_error_exit("malloc failed in inters_cube");
	res[1] = FAR;
	res[0] = FAR;
	if ((a = scal(obj->dir, ray->dir)) != 0)
	{
		b = scal(obj->dir, p);
		tmp = (obj->scale.z / 2.0 - b) / a;
		if (ft_incube(tmp, ray, obj))
			res[0] = tmp;
		tmp = (-obj->scale.z / 2.0 - b) / a;
		if (ft_incube(tmp, ray, obj))
		{
			if (res[0] == FAR)
				res[0] = tmp;
			else if (tmp != res[0])
				res[1] = tmp;
		}
	}
	if ((a = scal(obj->dir2, ray->dir)) != 0)
	{
		b = scal(obj->dir2, p);
		tmp = (obj->scale.y / 2.0 - b) / a;
		if (ft_incube(tmp, ray, obj))
		{
			if (res[0] == FAR)
				res[0] = tmp;
			else if (tmp != res[0])
				res[1] = tmp;
		}
		tmp = (-obj->scale.y / 2.0 - b) / a;
		if (ft_incube(tmp, ray, obj))
		{
			if (res[0] == FAR)
				res[0] = tmp;
			else if (tmp != res[0])
				res[1] = tmp;
		}
	}
	if ((a = scal(obj->dir3, ray->dir)) != 0)
	{
		b = scal(obj->dir3, p);
		tmp = (obj->scale.x / 2.0 - b) / a;
		if (ft_incube(tmp, ray, obj))
		{
			if (res[0] == FAR)
				res[0] = tmp;
			else if (tmp != res[0])
				res[1] = tmp;
		}
		tmp = (-obj->scale.x / 2.0 - b) / a;
		if (ft_incube(tmp, ray, obj))
		{
			if (res[0] == FAR)
				res[0] = tmp;
			else if (tmp != res[0])
				res[1] = tmp;
		}
	}
	if (res[0] > res[1])
	{
		tmp = res[0];
		res[0] = res[1];
		res[1] = tmp;
	}
	return(res);
}

double			*inters_pobj(t_ray *ray, t_obj *obj)
{
	t_list *tmp;
	double	vd;
	double	t;
	double	tdis;
	int		vndis;
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	double	s[3];
	double	*res;

	tmp = obj->face;
	tdis = FAR;
	vndis = 0;
	res = (double*)malloc(sizeof(double) * 2);
	res[1] = FAR;
	res[0] = FAR;
	while (tmp)
	{
		vd = (obj->vn)[((t_face*)(tmp->content))->vn].x * ray->dir.x +
			(obj->vn)[((t_face*)(tmp->content))->vn].y * ray->dir.y +
			(obj->vn)[((t_face*)(tmp->content))->vn].z * ray->dir.z;
		if (vd < 0)
		{
			t = ((obj->vn)[((t_face*)(tmp->content))->vn].x * ((obj->v)[((t_face*)(tmp->content))->v1].x - ray->pos.x) +
					(obj->vn)[((t_face*)(tmp->content))->vn].y * ((obj->v)[((t_face*)(tmp->content))->v1].y - ray->pos.y) +
					(obj->vn)[((t_face*)(tmp->content))->vn].z * ((obj->v)[((t_face*)(tmp->content))->v1].z - ray->pos.z)) / vd;
			if (t > 0)
			{
				u.x = (obj->v)[((t_face*)(tmp->content))->v1].x - (obj->v)[((t_face*)(tmp->content))->v3].x;
				u.y = (obj->v)[((t_face*)(tmp->content))->v1].y - (obj->v)[((t_face*)(tmp->content))->v3].y;
				u.z = (obj->v)[((t_face*)(tmp->content))->v1].z - (obj->v)[((t_face*)(tmp->content))->v3].z;
				v.x = (obj->v)[((t_face*)(tmp->content))->v2].x - (obj->v)[((t_face*)(tmp->content))->v3].x;
				v.y = (obj->v)[((t_face*)(tmp->content))->v2].y - (obj->v)[((t_face*)(tmp->content))->v3].y;
				v.z = (obj->v)[((t_face*)(tmp->content))->v2].z - (obj->v)[((t_face*)(tmp->content))->v3].z;
				w.x = ray->pos.x + t * ray->dir.x - (obj->v)[((t_face*)(tmp->content))->v3].x;
				w.y = ray->pos.y + t * ray->dir.y - (obj->v)[((t_face*)(tmp->content))->v3].y;
				w.z = ray->pos.z + t * ray->dir.z - (obj->v)[((t_face*)(tmp->content))->v3].z;
				s[0] = carre(scal(u,v)) - scal2(u) * scal2(v);
				s[1] = (scal(u,v) * scal(w,v) - scal2(v) * scal(w, u))/s[0];
				s[2] = (scal(u,v) * scal(w,u) - scal2(u) * scal(w, v))/s[0];
				if (s[1] >= 0 && s[2] >= 0 && (s[1] + s[2]) <= 1 && t < tdis)
				{
					tdis = t;
					vndis = ((t_face*)(tmp->content))->vn;
				}
			}
		}
		tmp = tmp->next;
	}
	if (tdis < FAR)
	{
		obj->norm.x = (obj->vn)[vndis].x;
		obj->norm.y = (obj->vn)[vndis].y;
		obj->norm.z = (obj->vn)[vndis].z;	
		res[0] = tdis;
	}
	return (res);
}
