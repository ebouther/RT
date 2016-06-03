/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:03:31 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/03 14:50:54 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_error_exit(const char *error)
{
	ft_putstr(error);
	exit(-1);
}

int		ft_ten_pow(int ten, int p)
{
	if (p <= 0)
		return (1);
	else
		return (ft_ten_pow(ten, p - 1) * 10);
}

double	ft_atod(char *s)
{
	t_norm_ft_atod	norm;

	norm.sgn = 1;
	norm.pt = 0;
	norm.res = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\v')
		s++;
	norm.sgn = *s;
	if (*s == '-' || *s == '+')
		s++;
	else if (*s == '+')
		s++;
	while ((*s >= '0' && *s <= '9') || (norm.pt == 0 && *s == '.'))
	{
		if (*s == '.' && norm.pt == 0)
			norm.pt = 1;
		else if (norm.pt)
			norm.pt *= 10;
		if (*s != '.')
			norm.res = (norm.pt == 0) ? norm.res * 10 + *s - '0' : norm.res
				+ (*s - '0') / (double)norm.pt;
		s++;
	}
	return (norm.sgn == '-' ? -norm.res : norm.res);
}

char	*ft_strjoin_free(char *s1, char *s2)
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
