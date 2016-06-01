/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 09:22:11 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 16:51:01 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_rot_vec(double angle, t_vec3 axe, t_vec3 *vec)
{
	t_vec3 norm;

	norm.x = axe.y * vec->z - axe.z * vec->y;
	norm.y = axe.z * vec->x - axe.x * vec->z;
	norm.z = axe.x * vec->y - axe.y * vec->x;
	vec->x = vec->x * cos(angle / 180 * M_PI_2) + norm.x
		* sin(angle / 180.0 * M_PI_2) + (1 - cos(angle / 180 * M_PI_2))
		* scal(axe, *vec) * axe.x;
	vec->y = vec->y * cos(angle / 180 * M_PI_2) + norm.y
		* sin(angle / 180.0 * M_PI_2) + (1 - cos(angle / 180 * M_PI_2))
		* scal(axe, *vec) * axe.y;
	vec->z = vec->z * cos(angle / 180 * M_PI_2) + norm.z
		* sin(angle / 180.0 * M_PI_2) + (1 - cos(angle / 180 * M_PI_2))
		* scal(axe, *vec) * axe.z;
}
