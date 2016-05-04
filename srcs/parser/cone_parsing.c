/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:49:15 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/04 16:59:34 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_cone(char *cone, t_env *e)
{
	char	*position;
	char	*direction;
	char	*angle;
	char	*mat;
	t_obj	cone_obj;

	cone_obj.mat.brim = 0.1;
	if ((position = ft_get_inner(cone, "position", NULL)) == NULL)
		ft_error_exit("Error: cone require a position subobject.\n");
	if ((angle = ft_get_inner(cone, "angle", NULL)) == NULL)
		ft_error_exit("Error: cone require an angle subobject.\n");
	if ((mat = ft_get_inner(cone, "mat", NULL)) == NULL)
		ft_error_exit("Error: cone require a material subobject.\n");
	if ((direction = ft_get_inner(cone, "direction", NULL)) == NULL)
		ft_error_exit("Error: cone require a direction subobject.\n");
	ft_set_vec3(position, &cone_obj.pos);
	ft_set_vec3(direction, &cone_obj.dir);
	ft_normalise(&cone_obj.dir);
	cone_obj.angle = ft_atod(angle) / 180 * M_PI;
	ft_set_mat(mat, &cone_obj);
	cone_obj.get_normal = &normal_cone;
	cone_obj.get_inters = &inters_cone;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cone_obj, sizeof(t_obj)));
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&angle);
	ft_strdel(&mat);
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
