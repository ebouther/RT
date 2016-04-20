/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:33:10 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/30 14:03:23 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *res;

	res = NULL;
	if (s == NULL)
		return (NULL);
	res = ft_strnew(len + 1);
	if (res == NULL)
		return (NULL);
	ft_strncpy(res, (char*)s + start, len);
	return (res);
}
