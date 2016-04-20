/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cal_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:21:39 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/20 15:05:28 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			ft_calc_ray(int x, int y, t_env *e)
{
	e->ray.x = e->cam.posx + e->cam.dirx * e->cam.distfo + ((double)WIDTH / 2.0)
		* (e->cam.upx - e->cam.rightx) + (double)WIDTH / (double)SIZE_W *
		(x * e->cam.rightx - y * e->cam.upx);
	e->ray.y = e->cam.posy + e->cam.diry * e->cam.distfo + ((double)WIDTH / 2.0)
		* (e->cam.upy - e->cam.righty) + (double)WIDTH / (double)SIZE_W *
		(x * e->cam.righty - y * e->cam.upy);
	e->ray.z = e->cam.posz + e->cam.dirz * e->cam.distfo + ((double)WIDTH / 2.0)
		* (e->cam.upz - e->cam.rightz) + (double)WIDTH / (double)SIZE_W *
		(x * e->cam.rightz - y * e->cam.upz);
	ft_normalise(&e->ray.x, &e->ray.y, &e->ray.z);
	e->ray.orix = e->cam.posx;
	e->ray.oriy = e->cam.posy;
	e->ray.oriz = e->cam.posz;
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
