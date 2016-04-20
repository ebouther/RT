/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fpower.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:02:39 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/07 17:20:02 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_fpower(double a, int b)
{
	double tmp;

	tmp = a;
	if (b == 0)
		return (1);
	else if (b == 1)
		return (a);
	else if (b < 0)
		return (0);
	while (b)
	{
		a = a * tmp;
		b--;
	}
	return (a);
}
