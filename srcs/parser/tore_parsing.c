/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 09:30:55 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 14:36:33 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_tore(char *tore, t_env *e, t_nod *prnt)
{
	char	*position;
	char	*direction;
	char	*radius;
	char	*radius2;
	char	*mat;
	char	*speed;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((position = ft_get_inner(tore, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require a position subobject.\n");
	if ((radius = ft_get_inner(tore, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require 2 radius subobject.\n");
	if ((radius2 = ft_get_inner(tore, "radius2", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require 2 radius subobject.\n");
	if ((mat = ft_get_inner(tore, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require a color subobject.\n");
	if ((direction = ft_get_inner(tore, "direction", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require a direction subobject.\n");
	if ((speed = ft_get_inner(tore, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(speed, &nod.obj->speed);
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
	nod.op = empty;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&radius);
	ft_strdel(&radius2);
	ft_strdel(&mat);
	ft_strdel(&speed);
	return (0);
}

int			ft_get_tores(char *objects, size_t len, t_env *e)
{
	char	*tore;
	int		pos;

	pos = 0;
	while ((tore = ft_get_inner(objects, "tore", &pos, NULL)) != NULL)
	{
		ft_set_tore(tore, e, NULL);
		ft_strdel(&tore);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
