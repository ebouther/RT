/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:46:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/31 14:35:43 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_plane(char *plane, t_env *e, t_nod *prnt)
{
	char	*position;
	char	*normal;
	char	*mat;
	char	*speed;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((position = ft_get_inner(plane, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: plane require a <position> subobject.\n");
	if ((normal = ft_get_inner(plane, "normal", NULL, NULL)) == NULL)
		ft_error_exit("Error: plane require a <normal> subobject.\n");
	if ((mat = ft_get_inner(plane, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: plane require a material subobject.\n");
	if ((speed = ft_get_inner(plane, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(speed, &nod.obj->speed);
	ft_set_vec3(position, &nod.obj->pos);
	ft_set_vec3(normal, &nod.obj->norm);
	ft_normalise(&nod.obj->norm);
	ft_set_mat(mat, nod.obj);
	nod.obj->get_normal = &normal_plan;
	nod.obj->get_inters = &inters_plan;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = empty;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	nod.obj_col->neg = 1;
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
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
	while ((plane = ft_get_inner(objects, "plane", &pos, NULL)) != NULL)
	{
		ft_set_plane(plane, e, NULL);
		ft_strdel(&plane);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
