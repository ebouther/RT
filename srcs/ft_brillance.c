/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_brillance.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:03:54 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/25 11:29:55 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			ft_brillance(t_vec3 *cam_dir, t_ray *ray, t_vec3 *normal)
{
	t_vec3 ref;
	double p;

	p = normal->x * ray->dir.x + normal->y * ray->dir.y + normal->z
		* ray->dir.z;
	ref.x = -ray->dir.x + 2 * normal->x * p;
	ref.y = -ray->dir.y + 2 * normal->y * p;
	ref.z = -ray->dir.z + 2 * normal->z * p;
	ft_normalise(&ref);
	p = ref.x * -cam_dir->x + ref.y * -cam_dir->y + ref.z * -cam_dir->z;
	return (p > 0 ? p : 0);
}
