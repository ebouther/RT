/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:37:10 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/27 11:56:59 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			let;
	size_t			i;
	char			*src;

	i = 0;
	let = (char)c;
	src = (char*)s;
	while (i < n)
	{
		if (src[i] == let)
			return (src + i);
		i++;
	}
	return (NULL);
}
