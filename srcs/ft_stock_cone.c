/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:35:48 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/10 14:45:29 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_cone1(t_env *e, char *c, int i, int nb)
{
	if (i == 1)
		e->obj[nb].angle = ft_atof(c) / 180 * M_PI;
	if (i == 2)
		e->obj[nb].directx = ft_atof(c);
	if (i == 3)
		e->obj[nb].directy = ft_atof(c);
	if (i == 4)
		e->obj[nb].directz = ft_atof(c);
	if (i == 5)
		e->obj[nb].centrex = ft_atof(c);
	if (i == 6)
		e->obj[nb].centrey = ft_atof(c);
	if (i == 7)
		e->obj[nb].centrez = ft_atof(c);
	if (i == 8)
		e->obj[nb].colr = ft_atof(c);
	if (i == 9)
		e->obj[nb].colg = ft_atof(c);
	if (i == 10)
		e->obj[nb].colb = ft_atof(c);
	if (i == 11)
		e->obj[nb].brim = ft_atof(c);
}

void		ft_stock_cone(t_env *e, char *line, int *nb)
{
	int		i;
	char	*c;

	i = 0;
	c = line;
	e->obj[*nb].type.cone = 1;
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_cone1(e, c, i, *nb);
		}
		else
			c++;
	}
	ft_normalise(&e->obj[*nb].directx, &e->obj[*nb + 1
			- 1].directy, &e->obj[*nb].directz);
	(*nb)++;
}
