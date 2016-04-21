/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:39:14 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 22:08:55 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_sphere1(char *c, int i, t_obj *obj)
{
	if (i == 1)
		obj->rayon = ft_atof(c);
	else if (i == 2)
		obj->pos.x = ft_atof(c);
	else if (i == 3)
		obj->pos.y = ft_atof(c);
	else if (i == 4)
		obj->pos.z = ft_atof(c);
	else if (i == 5)
		obj->mat.col.r = ft_atof(c);
	else if (i == 6)
		obj->mat.col.g = ft_atof(c);
	else if (i == 7)
		obj->mat.col.b = ft_atof(c);
	else if (i == 8)
		obj->mat.brim = ft_atof(c);
}

void		ft_stock_sphere(t_env *e, char *line)
{
	int		i;
	char	*c;
	t_obj	*obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	i = 0;
	c = line;
	obj->get_normal = &normal_sphere;
	obj->get_inters = &inters_sphere;
	while (*c != '}')
	{
		if (*c == '$')
		{
			i++;
			c++;
			ft_stock_sphere1(c, i, obj);
		}
		else
			c++;
	}
	ft_normalise(&obj->dir);
	ft_lstadd(&e->obj, ft_lstnew(obj, sizeof(t_obj)));
	free(obj);
}
