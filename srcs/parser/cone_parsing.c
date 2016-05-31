/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:49:15 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/31 09:45:01 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_cone_2(char *angle, char *position, char *direction,
				t_nod *nod)
{
	ft_set_vec3(position, &nod->obj->pos);
	ft_set_vec3(direction, &nod->obj->dir);
	ft_normalise(&nod->obj->dir);
	nod->obj->angle = ft_atod(angle) / 180 * M_PI;
	nod->obj->get_normal = &normal_cone;
	nod->obj->get_inters = &inters_cone;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = NULL;
	if ((nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col))) == NULL)
		exit(-1);
}

static int	ft_set_cone(char *cone, t_env *e)
{
	char	*position;
	char	*direction;
	char	*angle;
	char	*mat;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	nod.obj->mat.brim = 0.1;
	if ((position = ft_get_inner(cone, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require a position subobject.\n");
	if ((angle = ft_get_inner(cone, "angle", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require an angle subobject.\n");
	if ((mat = ft_get_inner(cone, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require a material subobject.\n");
	if ((direction = ft_get_inner(cone, "direction", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require a direction subobject.\n");
	ft_set_mat(mat, nod.obj);
	ft_set_cone_2(angle, position, direction, &nod);
	ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
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
	while ((cone = ft_get_inner(objects, "cone", &pos, NULL)) != NULL)
	{
		ft_set_cone(cone, e, NULL);
		ft_strdel(&cone);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
