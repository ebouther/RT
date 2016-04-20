/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:39:14 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/10 14:55:09 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_sphere1(t_env *e, char *c, int i, int nb)
{
	if (i == 1)
		e->obj[nb].rayon = ft_atof(c);
	if (i == 2)
		e->obj[nb].centrex = ft_atof(c);
	if (i == 3)
		e->obj[nb].centrey = ft_atof(c);
	if (i == 4)
		e->obj[nb].centrez = ft_atof(c);
	if (i == 5)
		e->obj[nb].colr = ft_atof(c);
	if (i == 6)
		e->obj[nb].colg = ft_atof(c);
	if (i == 7)
		e->obj[nb].colb = ft_atof(c);
	if (i == 8)
		e->obj[nb].brim = ft_atof(c);
}

void		ft_stock_sphere(t_env *e, char *line, int *nb)
{
	int		i;
	char	*c;

	i = 0;
	c = line;
	e->obj[*nb].type.sph = 1;
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_sphere1(e, c, i, *nb);
		}
		else
			c++;
	}
	(*nb)++;
}
