/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:13:59 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 16:49:02 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	carre(double x)
{
	return (x * x);
}

void	ft_normalise(t_vec3 *vec)
{
	double lg;

	lg = sqrt(carre(vec->x) + carre(vec->y) + carre(vec->z));
	if (lg == 0)
		return ;
	vec->x = vec->x / lg;
	vec->y = vec->y / lg;
	vec->z = vec->z / lg;
}

double	ft_norm(t_vec3 *vec)
{
	return (sqrt(carre(vec->x) + carre(vec->y) + carre(vec->z)));
}

double	ft_equa_sec(double a, double b, double c)
{
	double	delt;
	double	r1;
	double	r2;

	delt = carre(b) - 4 * a * c;
	if (delt < 0)
		return (FAR);
	else if (delt > 0)
	{
		r1 = (-b - sqrt(delt)) / (2 * a);
		r2 = (-b + sqrt(delt)) / (2 * a);
		if (r1 * r2 < 0)
		{
			if (r1 <= 0)
				return (r2);
			else
				return (r1);
		}
		else
			return (fmin(r1, r2));
	}
	else
		return (-b / (2 * a));
}
