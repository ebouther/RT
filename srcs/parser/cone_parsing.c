/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:49:15 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/16 14:12:26 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_cone(char *cone, t_env *e, t_nod *prnt)
{
	char	*position;
	char	*direction;
	char	*angle;
	char	*mat;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	nod.obj->mat.brim = 0.1;
	if ((position = ft_get_inner(cone, "position", NULL)) == NULL)
		ft_error_exit("Error: cone require a position subobject.\n");
	if ((angle = ft_get_inner(cone, "angle", NULL)) == NULL)
		ft_error_exit("Error: cone require an angle subobject.\n");
	if ((mat = ft_get_inner(cone, "mat", NULL)) == NULL)
		ft_error_exit("Error: cone require a material subobject.\n");
	if ((direction = ft_get_inner(cone, "direction", NULL)) == NULL)
		ft_error_exit("Error: cone require a direction subobject.\n");
	ft_set_vec3(position, &nod.obj->pos);
	ft_set_vec3(direction, &nod.obj->dir);
	ft_normalise(&nod.obj->dir);
	nod.obj->angle = ft_atod(angle) / 180 * M_PI;
	ft_set_mat(mat, nod.obj);
	nod.obj->get_normal = &normal_cone;
	nod.obj->get_inters = &inters_cone;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = NULL;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	nod.obj_col->neg = 1;
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
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
		ft_set_cone(cone, e, NULL);
		ft_strdel(&cone);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
