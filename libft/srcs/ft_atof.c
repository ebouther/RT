/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 09:20:16 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/02 09:07:32 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;

	c = (char *)str;
	res = (double)ft_atoi(c);
	while (*c != '.')
	{
		c++;
	}
	c++;
	res2 = (double)ft_atoi(c);
	return (res + res2 / ft_power(10, ft_strclen(' ', c) - 1));
}
