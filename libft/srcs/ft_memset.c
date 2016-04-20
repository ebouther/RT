/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:39:22 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/25 16:10:16 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			let;
	size_t			i;
	char			*str;

	let = (unsigned char)c;
	str = (char*)b;
	i = 0;
	while (i < len)
	{
		str[i] = let;
		i++;
	}
	return (str);
}
