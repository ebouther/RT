/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dist4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 09:57:59 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/02 10:32:30 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		ft_incube(double t, t_ray *ray, t_obj *obj)
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

static void		ft_sv_res(double *res, double tmp)
{
	if (res[0] == FAR)
		res[0] = tmp;
	else if (tmp != res[0])
		res[1] = tmp;
}

static void		ft_inters_cub2(t_vec3 *v,
		t_ray *ray, double *res, t_obj *obj)
{
	double	tmp;
	double	b;
	double	a;
	int		i;
	double	sc[3];

	i = 0;
	sc[0] = v[3].z;
	sc[1] = v[3].y;
	sc[2] = v[3].x;
	while (i < 3)
	{
		if ((a = scal(v[i], ray->dir)) != 0)
		{
			b = scal(v[i], v[4]);
			tmp = (sc[i] / 2.0 - b) / a;
			if (ft_incube(tmp, ray, obj))
				ft_sv_res(res, tmp);
			tmp = (-sc[i] / 2.0 - b) / a;
			if (ft_incube(tmp, ray, obj))
				ft_sv_res(res, tmp);
		}
		i++;
	}
}

static void		ft_swap_res(double *res)
{
	double	tmp;

	if (res[0] > res[1])
	{
		tmp = res[0];
		res[0] = res[1];
		res[1] = tmp;
	}
}

double			*inters_cube(t_ray *ray, t_obj *obj)
{
	double	*res;
	t_vec3	*v;
	t_vec3	p;

	p.x = ray->pos.x - obj->pos.x;
	p.y = ray->pos.y - obj->pos.y;
	p.z = ray->pos.z - obj->pos.z;
	if ((v = (t_vec3*)malloc(sizeof(t_vec3) * 5)) == NULL)
		ft_error_exit("malloc failed in inters_cube");
	if ((res = (double*)malloc(sizeof(double) * 2)) == NULL)
		ft_error_exit("malloc failed in inters_cube");
	res[1] = FAR;
	res[0] = FAR;
	v[0] = obj->dir;
	v[1] = obj->dir2;
	v[2] = obj->dir3;
	v[3] = obj->scale;
	v[4] = p;
	ft_inters_cub2(v, ray, res, obj);
	ft_swap_res(res);
	free(v);
	return (res);
}
