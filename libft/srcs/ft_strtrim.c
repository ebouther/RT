/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:34:10 by jbelless          #+#    #+#             */
/*   Updated: 2015/11/30 15:24:06 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	int		deb;
	int		fin;
	char	*res;

	if (s == NULL)
		return (NULL);
	res = NULL;
	deb = 0;
	fin = (int)ft_strlen(s) - 1;
	while (s[deb] == ' ' || s[deb] == '\n' || s[deb] == '\t')
		deb++;
	if (deb == (int)ft_strlen(s))
	{
		res = ft_strnew(1);
		return (res);
	}
	while (s[fin] == ' ' || s[fin] == '\n' || s[fin] == '\t')
		fin--;
	res = ft_strsub(s, deb, fin - deb + 1);
	return (res);
}
