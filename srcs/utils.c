/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:03:31 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/23 17:57:36 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error_exit(const char *error)
{
	ft_putstr(error);
	exit(-1);
}

int				ft_ten_pow(int ten, int p)
{
	if (p <= 0)
		return (1);
	else
		return (ft_ten_pow(ten, p - 1) * 10);
}

/*double			ft_atod(char *s)
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
		deci = deci / ft_ten_pow(1, j - i - 1);
		deci = deci + integer;
	}
	return (deci);
}*/

double		ft_atod(char *s)
{
	double	res;
	char	sgn;
	int		pt;

	sgn = 1;
	pt = 0;
	res = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\v')
		s++;
	sgn = *s;
	if (*s == '-' || *s == '+')
		s++;
	else if (*s == '+')
		s++;
	while ((*s >= '0' && *s <= '9') || (pt == 0 && *s == '.'))
	{
		if (*s == '.' && pt == 0)
			pt = 1;
		else if (pt)
			pt *= 10;
		if (*s != '.')
			res = (pt == 0) ? res * 10 + *s - '0'
							: res + (*s - '0') / (double)pt;
		s++;
	}
	return (sgn == '-' ? -res : res);
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
