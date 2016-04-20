/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:35:58 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/27 14:25:40 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*c1;
	char	*p;
	char	*res;

	c1 = ft_strnew(n + 1);
	ft_strncpy(c1, s1, n);
	p = ft_strstr(c1, s2);
	res = c1;
	free(c1);
	if (p == NULL)
		return (NULL);
	return ((char*)(s1 + (p - res)));
}
