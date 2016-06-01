/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_composed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 14:56:13 by ascholle          #+#    #+#             */
/*   Updated: 2016/06/01 11:00:58 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_set_cobjects(char *obj, t_nod *nod)
{
	t_set_cobj	c;

	c.unio = ft_get_inner(obj, "union", NULL, &c.u);
	c.substit = ft_get_inner(obj, "sub", NULL, &c.s);
	c.intersect = ft_get_inner(obj, "inters", NULL, &c.i);
	if (c.i != -1 && (c.i < c.s || c.s == -1) && (c.i < c.u || c.u == -1))
		ft_get_inter(c.intersect, NULL, nod);
	else if (c.u != -1 && (c.u < c.s || c.s == -1) && (c.u < c.i || c.i == -1))
		ft_get_union(c.unio, NULL, nod);
	else if (c.s != -1 && (c.s < c.i || c.i == -1) && (c.s < c.u || c.u == -1))
		ft_get_sub(c.substit, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "cylinder", NULL, NULL)) != NULL)
		ft_set_cylinder(c.form, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "sphere", NULL, NULL)) != NULL)
		ft_set_sphere(c.form, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "cone", NULL, NULL)) != NULL)
		ft_set_cone(c.form, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "plane", NULL, NULL)) != NULL)
		ft_set_plane(c.form, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "plane", NULL, NULL)) != NULL)
		ft_set_plane(c.form, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "tore", NULL, NULL)) != NULL)
		ft_set_tore(c.form, NULL, nod);
	else if ((c.form = ft_get_inner(obj, "cube", NULL, NULL)) != NULL)
		ft_set_cube(c.form, NULL, nod);
}

void	ft_get_union(char *unio, t_env *e, t_nod *prnt)
{
	char	*obj_1;
	char	*obj_2;
	char	*id;
	t_nod	nod;
	int		pos;

	if ((id = ft_get_inner(unio, "id", NULL, NULL)))
		nod.id = ft_atod(id);
	else
		nod.id = -1;
	if ((obj_1 = ft_get_inner(unio, "obj_1", &pos, NULL)) == NULL)
		ft_error_exit("ERROR: union require obj_1 subobject.\n");
	if ((obj_2 = ft_get_inner(unio + pos, "obj_2", NULL, NULL)) == NULL)
		ft_error_exit("ERROR: union require obj_2 subobject.\n");
	nod.obj = NULL;
	nod.obj_col = NULL;
	nod.op = uni;
	nod.r = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_2, nod.r);
	nod.l = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_1, nod.l);
	if (e)
		ft_lstadd(&e->c_obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
}

int		ft_get_inter(char *intersect, t_env *e, t_nod *prnt)
{
	char	*obj_1;
	char	*obj_2;
	char	*id;
	t_nod	nod;
	int		pos;

	if ((id = ft_get_inner(intersect, "id", NULL, NULL)))
		nod.id = ft_atod(id);
	if ((obj_1 = ft_get_inner(intersect, "obj_1", &pos, NULL)) == NULL)
		ft_error_exit("ERROR: inters require obj_1 subobject.\n");
	if ((obj_2 = ft_get_inner(intersect + pos, "obj_2", NULL, NULL)) == NULL)
		ft_error_exit("ERROR: inters require obj_2 subobject.\n");
	nod.obj = NULL;
	nod.obj_col = NULL;
	nod.op = inters;
	nod.r = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_2, nod.r);
	nod.l = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_1, nod.l);
	if (e)
		ft_lstadd(&e->c_obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	return (0);
}

int		ft_get_sub(char *substit, t_env *e, t_nod *prnt)
{
	char	*obj_1;
	char	*id;
	char	*obj_2;
	t_nod	nod;
	int		pos;

	if ((id = ft_get_inner(substit, "id", NULL, NULL)))
		nod.id = ft_atod(id);
	if ((obj_1 = ft_get_inner(substit, "obj_1", &pos, NULL)) == NULL)
		ft_error_exit("ERROR: sub require obj_1 subobject.\n");
	if ((obj_2 = ft_get_inner(substit + pos, "obj_2", NULL, NULL)) == NULL)
		ft_error_exit("ERROR: sub require obj_2 subobject.\n");
	nod.obj = NULL;
	nod.obj_col = NULL;
	nod.op = sub;
	nod.r = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_2, nod.r);
	nod.l = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_1, nod.l);
	if (e)
		ft_lstadd(&e->c_obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	return (0);
}
