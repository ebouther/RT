/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:01:32 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/30 15:42:30 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_digit(int nbr)
{
	int i;
	int tmp;

	i = 0;
	if (nbr < 0)
	{
		i++;
		tmp = -nbr;
	}
	else
		tmp = nbr;
	while (tmp / 10 > 0)
	{
		i++;
		tmp = tmp / 10;
	}
	return (i);
}

char		*ft_itoa(int nbr)
{
	char	*str;
	int		len;
	int		tmp;

	str = NULL;
	len = nb_digit(nbr);
	if ((str = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	tmp = nbr;
	if (nbr < 0)
		tmp = -nbr;
	if (nbr == -2147483648)
		return (str = ft_strcpy(str, "-2147483648"));
	if (nbr == 2147483647)
		return (str = ft_strcpy(str, "2147483647"));
	str[len + 1] = '\0';
	while (len + 1)
	{
		str[len] = (char)(tmp % 10 + 48);
		len--;
		tmp = tmp / 10;
	}
	if (nbr < 0)
		str[0] = '-';
	return (str);
}
