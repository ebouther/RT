/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:41:13 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/26 15:57:05 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	let;
	int		len;

	let = (char)c;
	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == let)
			return (&((char*)s)[len]);
		len--;
	}
	return (NULL);
}
