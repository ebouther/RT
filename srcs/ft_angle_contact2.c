/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_contact2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 09:45:01 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/04 16:55:22 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	*normal_tore(t_ray *ray, t_obj *obj)
{
	t_vec3	*res;
	t_vec3	cb;
	t_vec3	ch;
	double p;

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
	return (scal(*res, ray->dir) < 0 ? res : pro(-1, res));
}
