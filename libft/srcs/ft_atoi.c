/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:47:03 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/27 15:52:50 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test(const char *str, int *neg, int *sin, int *i)
{
	while (str[*i] == ' ' || str[*i] == '	' || str[*i] == '\n'
			|| str[*i] == '\t' || str[*i] == '\v' || str[*i] == '\f'
			|| str[*i] == '\r')
		*i = *i + 1;
	if (str[*i] == '+')
	{
		*i = *i + 1;
		*sin = 1;
	}
	if (str[*i] == '-' && !*sin)
	{
		*neg = 1;
		*i = *i + 1;
	}
	else if (str[*i] == '-' && *sin)
		return (0);
	if (str[*i] < '0' || str[*i] > '9')
		return (0);
	return (1);
}

int			ft_atoi(const char *str)
{
	int i;
	int neg;
	int res;
	int sin;

	neg = 0;
	i = 0;
	res = 0;
	sin = 0;
	if (!test(str, &neg, &sin, &i))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (int)(str[i] - '0');
		i++;
	}
	if (neg)
		return (-res);
	return (res);
}
