/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_plan.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:39:53 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/24 15:22:18 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_plan1(char *c, int i, t_obj *obj)
{
	if (i == 1)
		obj->norm.x = ft_atof(c);
	else if (i == 2)
		obj->norm.y = ft_atof(c);
	else if (i == 3)
		obj->norm.z = ft_atof(c);
	else if (i == 4)
		obj->pos.x = ft_atof(c);
	else if (i == 5)
		obj->pos.y = ft_atof(c);
	else if (i == 6)
		obj->pos.z = ft_atof(c);
	else if (i == 7)
		obj->mat.col.r = ft_atof(c);
	else if (i == 8)
		obj->mat.col.g = ft_atof(c);
	else if (i == 9)
		obj->mat.col.b = ft_atof(c);
	else if (i == 10)
		obj->mat.brim = ft_atof(c);
	else if (i == 11)
		obj->mat.ambiante = ft_atof(c);
}

void		ft_stock_plan(t_env *e, char *line)
{
	int		i;
	char	*c;
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	i = 0;
	c = line;
	obj->get_normal = &normal_plan;
	obj->get_inters = &inters_plan;
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_plan1(c, i, obj);
		}
		else
			c++;
	}
	ft_normalise(&obj->norm);
	ft_lstadd(&e->obj, ft_lstnew(obj, sizeof(t_obj)));
	free(obj);
}
