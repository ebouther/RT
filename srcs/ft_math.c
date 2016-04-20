/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:13:59 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/10 16:00:45 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	carre(double x)
{
	return (x * x);
}

void	ft_normalise(double *x, double *y, double *z)
{
	double lg;

	lg = sqrt(carre(*x) + carre(*y) + carre(*z));
	*x = *x / lg;
	*y = *y / lg;
	*z = *z / lg;
}

double	ft_norm(double x, double y, double z)
{
	return (sqrt(carre(x) + carre(y) + carre(z)));
}

double	ft_equa_sec(double a, double b, double c)
{
	double delt;

	delt = carre(b) - 4 * a * c;
	if (delt < 0)
		return (1000000000);
	else if (delt > 0)
		return (fmin((-b - sqrt(delt)) / (2 * a), (-b + sqrt(delt)) / (2 * a)));
	else
		return (-b / (2 * a));
}
