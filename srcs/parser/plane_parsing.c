/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:46:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/10 11:13:41 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
static int	ft_set_plane(char *plane, t_env *e)
{
	char	*position;
	char	*normal;
	char	*mat;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	nod.obj->mat.brim = 0.1;
	if ((position = ft_get_inner(plane, "position", NULL)) == NULL)
		ft_error_exit("Error: plane require a <position> subobject.\n");
	if ((normal = ft_get_inner(plane, "normal", NULL)) == NULL)
		ft_error_exit("Error: plane require a <normal> subobject.\n");
	if ((mat = ft_get_inner(plane, "mat", NULL)) == NULL)
		ft_error_exit("Error: plane require a material subobject.\n");
	ft_set_vec3(position, &nod.obj->pos);
	ft_set_vec3(normal, &nod.obj->norm);
	ft_normalise(&nod.obj->norm);
	ft_set_mat(mat, nod.obj);
	nod.obj->get_normal = &normal_plan;
	nod.obj->get_inters = &inters_plan;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = NULL;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
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
