/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cal_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:21:39 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 16:32:42 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		*ft_calc_ray(int x, int y, t_env *e)
{
	t_ray *ray;

	if ((ray = (t_ray *)malloc(sizeof(t_ray))) == NULL)
		exit(-1);
	ray->dir.x = e->cam.pos.x + e->cam.dir.x * e->cam.distfo + ((double)HIGHT / 2.0) * e->cam.up.x - ((double)WIDTH / 2.0) * e->cam.right.x + ((double)WIDTH / (double)SIZE_W) * x * e->cam.right.x - ((double)HIGHT / (double)SIZE_H) * y * e->cam.up.x;
	ray->dir.y = e->cam.pos.y + e->cam.dir.y * e->cam.distfo + ((double)WIDTH / 2.0) * (e->cam.up.y - e->cam.right.y) + ((double)WIDTH / (double)SIZE_W) * y * e->cam.right.y - ((double)WIDTH / (double)SIZE_H) * y * e->cam.up.y;
	ray->dir.z = e->cam.pos.z + e->cam.dir.z * e->cam.distfo + ((double)WIDTH / 2.0) * (e->cam.up.z - e->cam.right.z) + ((double)WIDTH / (double)SIZE_W) * y * e->cam.right.z - ((double)WIDTH / (double)SIZE_H) * y * e->cam.up.z;
	ft_normalise(&ray->dir);
	ray->pos.x = e->cam.pos.x;
	ray->pos.y = e->cam.pos.y;
	ray->pos.z = e->cam.pos.z;
	return (ray);
}

double			ft_dist_light(t_env *e, int i)
{
	return (sqrt(carre(e->light[i].centrex - e->ray.orix) +
				carre(e->light[i].centrey - e->ray.oriy) +
				carre(e->light[i].centrez - e->ray.oriz)));
}

void			ft_recalc_ori(t_env *e)
{
	e->ray.oeilx = -e->ray.x;
	e->ray.oeily = -e->ray.y;
	e->ray.oeilz = -e->ray.z;
	ft_normalise(&e->ray.oeilx, &e->ray.oeily, &e->ray.oeilz);
	e->ray.orix = e->ray.orix + e->ray.t * 0.9999 * e->ray.x;
	e->ray.oriy = e->ray.oriy + e->ray.t * 0.9999 * e->ray.y;
	e->ray.oriz = e->ray.oriz + e->ray.t * 0.9999 * e->ray.z;
}

void			ft_recalc_dir(t_env *e, int i)
{
	e->ray.x = e->light[i].centrex - e->ray.orix;
	e->ray.y = e->light[i].centrey - e->ray.oriy;
	e->ray.z = e->light[i].centrez - e->ray.oriz;
	ft_normalise(&e->ray.x, &e->ray.y, &e->ray.z);
}
