/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 09:34:57 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/03 09:01:03 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbmot(const char *s, char c)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (s[j] == c)
		j++;
	while (s[j])
	{
		if (s[j] != c && (j == 0 || s[j - 1] == c))
			i++;
		j++;
	}
	return (i);
}

static int	ft_strclen1(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = NULL;
	if (s == NULL)
		return (NULL);
	if ((res = (char **)malloc((sizeof(char *) * (ft_nbmot(s, c))))) == NULL)
		return (NULL);
	while (s[j] == c)
		j++;
	while (s[j])
	{
		if (s[j] != c && (j == 0 || s[j - 1] == c))
		{
			res[i] = ft_strnew(ft_strclen1(s + j, c));
			ft_strncpy(res[i], s + j, ft_strclen1(s + j, c));
			i++;
		}
		j++;
	}
	res[i] = NULL;
	return (res);
}
