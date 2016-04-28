/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:45:04 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/28 15:13:50 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_cylinder(char *cylinder, t_env *e)
{
	char	*position;
	char	*direction;
	char	*radius;
	char	*color;
	t_obj	cylinder_obj;

	cylinder_obj.mat.brim = 0.1;
	if ((position = ft_get_inner(cylinder, "position", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a position subobject.\n");
	if ((radius = ft_get_inner(cylinder, "radius", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a radius subobject.\n");
	if ((color = ft_get_inner(cylinder, "color", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a color subobject.\n");
	if ((direction = ft_get_inner(cylinder, "direction", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a direction subobject.\n");
	ft_set_vec3(position, &cylinder_obj.pos);
	ft_set_vec3(direction, &cylinder_obj.dir);
	ft_normalise(&cylinder_obj.dir);
	cylinder_obj.rayon = ft_atod(radius);
	ft_set_color(color, &cylinder_obj.mat.col);
	cylinder_obj.get_normal = &normal_cyl;
	cylinder_obj.get_inters = &inters_cyl;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cylinder_obj, sizeof(t_obj)));
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&radius);
	ft_strdel(&color);
	return (0);
}

int			ft_get_cylinders(char *objects, size_t len, t_env *e)
{
	char	*cylinder;
	int		pos;

	pos = 0;
	while ((cylinder = ft_get_inner(objects, "cylinder", &pos)) != NULL)
	{
		ft_set_cylinder(cylinder, e);
		ft_strdel(&cylinder);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
