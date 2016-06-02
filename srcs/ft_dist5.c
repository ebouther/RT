/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 09:20:04 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/02 11:30:17 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		ft_in_triangle(t_face *tmp, t_ray *ray, t_obj *obj,
		double t)
{
	t_vec3	v[3];
	double	s[3];

	v[0].x = (obj->v)[tmp->v1].x - (obj->v)[tmp->v3].x;
	v[0].y = (obj->v)[tmp->v1].y - (obj->v)[tmp->v3].y;
	v[0].z = (obj->v)[tmp->v1].z - (obj->v)[tmp->v3].z;
	v[1].x = (obj->v)[tmp->v2].x - (obj->v)[tmp->v3].x;
	v[1].y = (obj->v)[tmp->v2].y - (obj->v)[tmp->v3].y;
	v[1].z = (obj->v)[tmp->v2].z - (obj->v)[tmp->v3].z;
	v[2].x = ray->pos.x + t * ray->dir.x - (obj->v)[tmp->v3].x;
	v[2].y = ray->pos.y + t * ray->dir.y - (obj->v)[tmp->v3].y;
	v[2].z = ray->pos.z + t * ray->dir.z - (obj->v)[tmp->v3].z;
	s[0] = carre(scal(v[0], v[1])) - scal2(v[0]) * scal2(v[1]);
	s[1] = (scal(v[0], v[1]) * scal(v[2], v[1]) -
			scal2(v[1]) * scal(v[2], v[0])) / s[0];
	s[2] = (scal(v[0], v[1]) * scal(v[2], v[0]) -
			scal2(v[0]) * scal(v[2], v[1])) / s[0];
	if (s[1] >= 0 && s[2] >= 0 && (s[1] + s[2]) <= 1)
		return (1);
	return (0);
}

static int		ft_pobj2(t_obj *obj, t_ray *ray, t_face *tmp, double *tdis)
{
	double	vd;
	double	t;

	vd = (obj->vn)[tmp->vn].x * ray->dir.x +
		(obj->vn)[tmp->vn].y * ray->dir.y +
		(obj->vn)[tmp->vn].z * ray->dir.z;
	if (vd < 0)
	{
		t = ((obj->vn)[tmp->vn].x * ((obj->v)[tmp->v1].x - ray->pos.x) +
				(obj->vn)[tmp->vn].y * ((obj->v)[tmp->v1].y - ray->pos.y) +
				(obj->vn)[tmp->vn].z * ((obj->v)[tmp->v1].z - ray->pos.z)) / vd;
		if (t > 0)
		{
			if (ft_in_triangle(tmp, ray, obj, t) && t < *tdis)
			{
				*tdis = t;
				return (tmp->vn);
			}
		}
	}
	return (-1);
}

static void		ft_res_pobj(t_obj *obj, int vndis, double *res, double tdis)
{
	obj->norm.x = (obj->vn)[vndis].x;
	obj->norm.y = (obj->vn)[vndis].y;
	obj->norm.z = (obj->vn)[vndis].z;
	res[0] = tdis;
}

double			*inters_pobj(t_ray *ray, t_obj *obj)
{
	t_list	*tmp;
	double	tdis;
	int		vndis;
	int		v_t;
	double	*res;

	tmp = obj->face;
	tdis = FAR;
	vndis = 0;
	res = (double*)malloc(sizeof(double) * 2);
	res[1] = FAR;
	res[0] = FAR;
	while (tmp)
	{
		if ((v_t = ft_pobj2(obj, ray, ((t_face*)(tmp->content)), &tdis)) != -1)
			vndis = v_t;
		tmp = tmp->next;
	}
	if (tdis < FAR)
		ft_res_pobj(obj, vndis, res, tdis);
	return (res);
}
