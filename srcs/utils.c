/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:03:31 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/25 16:39:09 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error_exit(const char *error)
{
	ft_putstr(error);
	exit(-1);
}

double			ft_atod(char *s)
{
	int			i;
	int			j;
	double		integer;
	double		deci;

	i = 0;
	deci = 0.0;
	while (s[i] && s[i] != '.')
		i++;
	if (s[i] == '\0')
		return ((double)(ft_atoi(s)));
	else if (s[i] == '.')
	{
		integer = (double)ft_atoi(ft_strsub(s, 0, i));
		deci = (double)ft_atoi(ft_strsub(s, i + 1, ft_strlen(s) - i - 1));
		j = i + 1;
		while (ft_isdigit(s[j]) == 1)
			j++;
		deci = deci / pow(j - i - 1, 10);
		deci = deci + integer;
	}
	return (deci);
}

char		*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = NULL;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	if ((join = (char *)malloc(sizeof(char) * (ft_strlen(s1)
						+ ft_strlen(s2) + 1))) == NULL)
		return (NULL);
	ft_strcpy(join, s1);
	ft_strcat(join, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (join);
}
