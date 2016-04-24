/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/01 09:20:16 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/24 15:46:35 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	virgule(const char *nptr, const char *base, size_t bs	, size_t b)
{
	int	coef;
	double	res;

	res = 0;
	coef = bs;
	while (*nptr >= base[0] && *nptr <= base[b])
	{
		res += (ft_strchr(base, *nptr) - base) / (double)coef;
		coef *= bs;
		nptr++;
	}
	return (res);
}

double	ft_atoi_base(const char *nptr, const char *base)
{
	double	res;
	int		signe;
	size_t	base_size;
	size_t	max_ibase;

	res = 0;
	signe = 1;
	base_size = ft_strlen(base);
	max_ibase = base_size - 1;
	nptr = (nptr[0] == '0' && nptr[1] == 'x') ? nptr + 2 : nptr;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if ((*nptr == '-' && (signe = -1)) || *nptr == '+')
		nptr++;
	while (*nptr >= base[0] && *nptr <= base[max_ibase])
	{
		res = res * base_size + (double)(ft_strchr(base, *nptr) - base);
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		res += virgule(nptr, base, base_size, max_ibase);
	}
	return (res * (double)signe);
}


double	ft_atof(const char *str)
{/*
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
*/
	return (ft_atoi_base(str, "0123456789"));
}
