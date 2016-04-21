/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brillance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:03:54 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 22:11:39 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			ft_brillance(t_vec3 *pos_cam, t_ray *ray, t_vec3 *normal)
{
	t_vec3 ref;
	double p;

	p = normal->x * e->ray.x + normal->y * e->ray.y + normal->z * e->ray.z;
	ref.x = -e->ray.x + 2 * normal->x * p;
	ref.y = -e->ray.y + 2 * normal->y * p;
	ref.z = -e->ray.z + 2 * normal->z * p;
	ft_normalise(&ref);
	return (ref.x * pos_cam->x + ref.y * pos_cam->y + ref.z * pos_cam->z);
}
