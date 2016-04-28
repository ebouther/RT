/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:46:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/28 14:35:09 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_plane(char *plane, t_env *e)
{
	char	*position;
	char	*normal;
	char	*mat;
	t_obj	plane_obj;

	plane_obj.mat.brim = 0.1;
	if ((position = ft_get_inner(plane, "position", NULL)) == NULL)
		ft_error_exit("Error: plane require a <position> subobject.\n");
	if ((normal = ft_get_inner(plane, "normal", NULL)) == NULL)
		ft_error_exit("Error: plane require a <normal> subobject.\n");
	if ((mat = ft_get_inner(plane, "mat", NULL)) == NULL)
		ft_error_exit("Error: plane require a material subobject.\n");
	ft_set_vec3(position, &plane_obj.pos);
	ft_set_vec3(normal, &plane_obj.norm);
	ft_set_mat(mat, &plane_obj);
	plane_obj.get_normal = &normal_plan;
	plane_obj.get_inters = &inters_plan;
	ft_lstadd(&e->obj, ft_lstnew((void *)&plane_obj, sizeof(t_obj)));
	ft_strdel(&position);
	ft_strdel(&normal);
	ft_strdel(&mat);
	return (0);
}

int			ft_get_planes(char *objects, size_t len, t_env *e)
{
	char	*plane;
	int		pos;

	pos = 0;
	while ((plane = ft_get_inner(objects, "plane", &pos)) != NULL)
	{
		ft_set_plane(plane, e);
		ft_strdel(&plane);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
