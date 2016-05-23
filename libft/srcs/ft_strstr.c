/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:01:07 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/23 18:16:32 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strstr(const char *in, const char *str)
{
	char	c;
	size_t	len;
	char	sc;

	c = *str++;
	if (!c)
		return ((char *)in);
	len = ft_strlen(str);
	while (ft_strncmp(in, str, len) != 0)
	{
		sc = *in++;
		while (sc != c)
		{
			sc = *in++;
			if (!sc)
				return (NULL);
		}
	} 
	return ((char *)(in - 1));
}
