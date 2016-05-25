/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_composed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 14:56:13 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/24 14:45:07 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_set_cobjects(char *obj, t_nod *nod)
{
	char	*form;
	char	*unio;
	char	*sub;
	char	*inters;
	int		i;
	int		u;
	int		s;

	unio = ft_get_inner(obj, "union", NULL, &u);
	sub = ft_get_inner(obj, "sub", NULL, &s);
	inters = ft_get_inner(obj, "inters", NULL, &i);
	if (i != -1 && (i < s || s == -1) && (i < u || u == -1))
			ft_get_inter(inters, NULL, nod);
	else if (u != -1 && (u < s || s == -1) && (u < i || i == -1))
			ft_get_union(unio, NULL, nod);
	else if (s != -1 && (s < i || i == -1) && (s < u || u == -1))
			ft_get_sub(sub, NULL, nod);
	else if ((form = ft_get_inner(obj, "cylinder", NULL, NULL)) != NULL)
			ft_set_cylinder(form, NULL, nod);
	else if ((form = ft_get_inner(obj, "sphere", NULL, NULL)) != NULL)
			ft_set_sphere(form, NULL, nod);
	else if ((form = ft_get_inner(obj, "cone", NULL, NULL)) != NULL)
			ft_set_cone(form, NULL, nod);
	else if ((form = ft_get_inner(obj, "plane", NULL, NULL)) != NULL)
			ft_set_plane(form, NULL, nod);
	else if ((form = ft_get_inner(obj, "plane", NULL, NULL)) != NULL)
			ft_set_plane(form, NULL, nod);
	else if ((form = ft_get_inner(obj, "tore", NULL, NULL)) != NULL)
			ft_set_tore(form, NULL, nod);
}

int		ft_get_union(char *unio, t_env *e, t_nod *prnt)
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
	nod.op = &ft_union_obj;
	nod.r = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_1, nod.r);
	nod.l = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_2, nod.l);
	if (e)
		ft_lstadd(&e->c_obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	return (0);
}

int		ft_get_inter(char *inters, t_env *e, t_nod *prnt)
{
	char	*obj_1;
	char	*obj_2;
	char	*id;
	t_nod	nod;
	int		pos;

	if ((id = ft_get_inner(inters, "id", NULL, NULL)))
		nod.id = ft_atod(id);
	if ((obj_1 = ft_get_inner(inters, "obj_1", &pos, NULL)) == NULL)
		ft_error_exit("ERROR: inters require obj_1 subobject.\n");
	if ((obj_2 = ft_get_inner(inters + pos, "obj_2", NULL, NULL)) == NULL)
		ft_error_exit("ERROR: inters require obj_2 subobject.\n");
	nod.obj = NULL;
	nod.obj_col = NULL;
	nod.op = &ft_inters_obj;
	nod.r = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_1, nod.r);
	nod.l = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_2, nod.l);
	if (e)
		ft_lstadd(&e->c_obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	return (0);
}

int		ft_get_sub(char *sub, t_env *e, t_nod *prnt)
{
	char	*obj_1;
	char	*id;
	char	*obj_2;
	t_nod	nod;
	int		pos;

	if ((id = ft_get_inner(sub, "id", NULL, NULL)))
		nod.id = ft_atod(id);
	if ((obj_1 = ft_get_inner(sub, "obj_1", &pos, NULL)) == NULL)
		ft_error_exit("ERROR: sub require obj_1 subobject.\n");
	if ((obj_2 = ft_get_inner(sub + pos, "obj_2", NULL, NULL)) == NULL)
		ft_error_exit("ERROR: sub require obj_2 subobject.\n");
	nod.obj = NULL;
	nod.obj_col = NULL;
	nod.op = &ft_sub_obj;
	nod.r = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_1, nod.r);
	nod.l = (t_nod *)malloc(sizeof(t_nod));
	ft_set_cobjects(obj_2, nod.l);
	if (e)
		ft_lstadd(&e->c_obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	return (0);
}
