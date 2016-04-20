/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:41:25 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/10 15:01:45 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_light1(t_env *e, char *c, int i, int nb)
{
	if (i == 1)
		e->light[nb].centrex = ft_atof(c);
	if (i == 2)
		e->light[nb].centrey = ft_atof(c);
	if (i == 3)
		e->light[nb].centrez = ft_atof(c);
	if (i == 4)
		e->light[nb].colr = ft_atof(c);
	if (i == 5)
		e->light[nb].colg = ft_atof(c);
	if (i == 6)
		e->light[nb].colb = ft_atof(c);
}

void		ft_stock_light(t_env *e, char *line, int *nb)
{
	int		i;
	char	*c;

	i = 0;
	c = line;
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_light1(e, c, i, *nb);
		}
		else
			c++;
	}
	(*nb)++;
}
