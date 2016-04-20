/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:01:07 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/27 13:11:21 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	char	*c1;
	size_t	i;

	c1 = (char*)s1;
	i = 0;
	if (*c1 == 0 && *s2)
		return (NULL);
	if (*s2 == 0)
		return (c1);
	if (*c1 != *s2)
		return (ft_strstr(c1 + 1, s2));
	else
	{
		while (c1[i] == s2[i] && c1[i] && s2[i])
			i++;
		if (i == ft_strlen(s2))
			return (c1);
		else if (c1[i])
			return (ft_strstr(c1 + 1, s2));
	}
	return (NULL);
}
