/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 09:30:55 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/10 15:26:28 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_tore(char *tore, t_env *e)
{
	char	*position;
	char	*direction;
	char	*radius;
	char	*radius2;
	char	*mat;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	nod.obj->mat.brim = 0.1;
	if ((position = ft_get_inner(tore, "position", NULL)) == NULL)
		ft_error_exit("Error: tore require a position subobject.\n");
	if ((radius = ft_get_inner(tore, "radius", NULL)) == NULL)
		ft_error_exit("Error: tore require 2 radius subobject.\n");
	if ((radius2 = ft_get_inner(tore, "radius2", NULL)) == NULL)
		ft_error_exit("Error: tore require 2 radius subobject.\n");
	if ((mat = ft_get_inner(tore, "mat", NULL)) == NULL)
		ft_error_exit("Error: tore require a color subobject.\n");
	if ((direction = ft_get_inner(tore, "direction", NULL)) == NULL)
		ft_error_exit("Error: tore require a direction subobject.\n");
	ft_set_vec3(position, &nod.obj->pos);
	ft_set_vec3(direction, &nod.obj->dir);
	ft_normalise(&nod.obj->dir);
	nod.obj->rayon = ft_atod(radius);
	nod.obj->rayon2 = ft_atod(radius2);
	ft_set_mat(mat, nod.obj);
	nod.obj->get_normal = &normal_tore;
	nod.obj->get_inters = &inters_tore;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = NULL;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&radius);
	ft_strdel(&radius2);
	ft_strdel(&mat);
	return (0);
}

int			ft_get_tores(char *objects, size_t len, t_env *e)
{
	char	*tore;
	int		pos;

	pos = 0;
	while ((tore = ft_get_inner(objects, "tore", &pos)) != NULL)
	{
		ft_set_tore(tore, e);
		ft_strdel(&tore);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
