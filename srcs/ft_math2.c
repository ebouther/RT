/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 11:38:02 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/10 13:53:33 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	scal(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	scal2(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec3	*pro(double a, t_vec3 *d)
{
	d->x = (d->x != 0 ? d->x * a : 0);
	d->y = (d->y != 0 ? d->y * a : 0);
	d->z = (d->z != 0 ? d->z * a : 0);
	return (d);
}
