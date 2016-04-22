/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cal_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:21:39 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/22 15:00:20 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray		*ft_calc_ray(int x, int y, t_env *e)
{
	t_ray *ray;

	if ((ray = (t_ray *)malloc(sizeof(t_ray))) == NULL)
		exit(-1);
	ray->dir.x = e->cam.pos.x + e->cam.dir.x * e->cam.distfo + e->pix_zero.x + ((double)WIDTH / (double)SIZE_W) * x * e->cam.right.x - ((double)HIGHT / (double)SIZE_H) * y * e->cam.up.x;
	ray->dir.y = e->cam.pos.y + e->cam.dir.y * e->cam.distfo + e->pix_zero.y + ((double)WIDTH / (double)SIZE_W) * y * e->cam.right.y - ((double)HIGHT / (double)SIZE_H) * y * e->cam.up.y;
	ray->dir.z = e->cam.pos.z + e->cam.dir.z * e->cam.distfo + e->pix_zero.z + ((double)WIDTH / (double)SIZE_W) * y * e->cam.right.z - ((double)HIGHT / (double)SIZE_H) * y * e->cam.up.z;
	ft_normalise(&ray->dir);
	ray->pos.x = e->cam.pos.x;
	ray->pos.y = e->cam.pos.y;
	ray->pos.z = e->cam.pos.z;
	return (ray);
}

double			ft_dist_light(t_vec3 *ray_pos, t_vec3 *light_pos)
{
	return (sqrt(carre(light_pos->x - ray_pos->x) +
				carre(light_pos->y - ray_pos->y) +
				carre(light_pos->z - ray_pos->z)));
}

t_ray	 *ft_recalc_ori(t_ray *ray, double t)
{
	t_ray	*res;
	int		i;

	i = 0;
	res = (t_ray*)malloc(sizeof(t_ray) * 3);
	while(i < 3)
	{
		res[i].pos.x = ray->pos.x + ray->dir.x * t * 0.9999;
		res[i].pos.y = ray->pos.y + ray->dir.y * t * 0.9999;
		res[i].pos.z = ray->pos.z + ray->dir.z * t * 0.9999;
		i++;
	}	
	return (res);
}

void			ft_recalc_dir(t_light *light, t_ray *ray)
{
	ray->dir.x = light->pos.x - ray->pos.x;
	ray->dir.y = light->pos.y - ray->pos.y;
	ray->dir.z = light->pos.z - ray->pos.z;
	ft_normalise(&(ray->dir));
}
