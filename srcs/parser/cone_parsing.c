/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:49:15 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/26 14:08:40 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_cone(char *cone, t_env *e)
{
	char	*position;
	char	*direction;
	char	*angle;
	char	*color;
	t_obj	cone_obj;

	if ((position = ft_get_inner(cone, "position", NULL)) == NULL)
		ft_error_exit("Error: cone require a position subobject.\n");
	if ((angle = ft_get_inner(cone, "angle", NULL)) == NULL)
		ft_error_exit("Error: cone require an angle subobject.\n");
	if ((color = ft_get_inner(cone, "color", NULL)) == NULL)
		ft_error_exit("Error: cone require a color subobject.\n");
	if ((direction = ft_get_inner(cone, "direction", NULL)) == NULL)
		ft_error_exit("Error: cone require a direction subobject.\n");
	ft_set_vec3(position, &cone_obj.pos);
	ft_set_vec3(direction, &cone_obj.dir);
	cone_obj.angle = ft_atod(angle) / 180 * M_PI;
	ft_set_color(color, &cone_obj.mat.col);
	
	//Temp
	cone_obj.mat.brim = 0.5;
	cone_obj.mat.ambiante = 0.2;

	cone_obj.get_normal = &normal_cone;
	cone_obj.get_inters = &inters_cone;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cone_obj, sizeof(t_obj)));
	return (0);
}

int			ft_get_cones(char *objects, size_t len, t_env *e)
{
	char	*cone;
	int		pos;

	pos = 0;
	while ((cone = ft_get_inner(objects, "cone", &pos)) != NULL)
	{
		ft_set_cone(cone, e);
		ft_strdel(&cone);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
