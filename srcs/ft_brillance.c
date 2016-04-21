/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brillance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:03:54 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 23:13:47 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			ft_brillance(t_vec3 *pos_cam, t_ray *ray, t_vec3 *normal)
{
	t_vec3 ref;
	double p;

	p = normal->x * ray->dir.x + normal->y * ray->dir.y + normal->z * ray->dir.z;
	ref.x = -ray->dir.x + 2 * normal->x * p;
	ref.y = -ray->dir.y + 2 * normal->y * p;
	ref.z = -ray->dir.z + 2 * normal->z * p;
	ft_normalise(&ref);
	return (ref.x * pos_cam->x + ref.y * pos_cam->y + ref.z * pos_cam->z);
}
