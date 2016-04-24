/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:41:25 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/24 14:03:44 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_light1(char *c, int i, t_light *light)
{
	if (i == 1)
		light->pos.x = ft_atof(c);
	else if (i == 2)
		light->pos.y = ft_atof(c);
	else if (i == 3)
		light->pos.z = ft_atof(c);
	else if (i == 4)
		light->col.r = ft_atof(c);
	else if (i == 5)
		light->col.g = ft_atof(c);
	else if (i == 6)
		light->col.b = ft_atof(c);
	else if (i == 7)
		light->k = ft_atof(c);
}

void		ft_stock_light(t_env *e, char *line)
{
	int		i;
	char	*c;
	t_light	*light;

	i = 0;
	c = line;
	light = (t_light*)malloc(sizeof(t_light));
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_light1(c, i, light);
		}
		else
			c++;
	}
	ft_lstadd(&e->light, ft_lstnew(light, sizeof(t_light)));
	free(light);
}
