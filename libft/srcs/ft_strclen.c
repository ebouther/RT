/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 09:06:48 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/02 09:06:50 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strclen(char c, const char *str)
{
	char	*tmp;
	size_t	res;

	tmp = (char *)str;
	res = 0;
	if (str == NULL)
		return (0);
	while (*tmp && *tmp != c)
	{
		tmp++;
		res++;
	}
	return (res);
}
