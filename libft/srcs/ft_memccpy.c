/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:44:42 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/27 11:54:11 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*dst_tmp;
	char			*src_tmp;
	char			let;
	size_t			i;

	i = 0;
	src_tmp = (char*)src;
	dst_tmp = (char*)dst;
	let = (char)c;
	while (i < n && src_tmp[i] != let)
	{
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
		return (dst + i + 1);
}
