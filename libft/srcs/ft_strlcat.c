/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:28:57 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/26 15:24:25 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size <= i)
		return (j + size);
	if (size == i + 1)
		return (j + i);
	if (size > i + 1 && size <= i + j + 1)
		ft_strncat(dst, src, size - i - 1);
	if (size > i + j + 1)
		ft_strcat(dst, src);
	return (i + j);
}
