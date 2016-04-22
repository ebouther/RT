/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_cyl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:40:35 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/22 15:13:38 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_cyl1(char *c, int i, t_obj *obj)
{
	if (i == 1)
		obj->rayon = ft_atof(c);
	else if (i == 2)
		obj->dir.x = ft_atof(c);
	else if (i == 3)
		obj->dir.y = ft_atof(c);
	else if (i == 4)
		obj->dir.z = ft_atof(c);
	else if (i == 5)
		obj->pos.x = ft_atof(c);
	else if (i == 6)
		obj->pos.y = ft_atof(c);
	else if (i == 7)
		obj->pos.z = ft_atof(c);
	else if (i == 8)
		obj->mat.col.r = ft_atof(c);
	else if (i == 9)
		obj->mat.col.g = ft_atof(c);
	else if (i == 10)
		obj->mat.col.b = ft_atof(c);
	else if (i == 11)
		obj->mat.brim = ft_atof(c);
}

#include <stdio.h>

void		ft_stock_cyl(t_env *e, char *line)
{
	int		i;
	char	*c;
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	i = 0;
	c = line;
	obj->get_normal = &normal_cyl;
	obj->get_inters = &inters_cyl;
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_cyl1(c, i, obj);
		}
		else
			c++;
	}
	ft_normalise(&obj->dir);
	ft_lstadd(&e->obj, ft_lstnew(obj, sizeof(t_obj)));
	printf("brim = %f\n", obj->mat.brim);
	free(obj);
}
