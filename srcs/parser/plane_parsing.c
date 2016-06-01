/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:46:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 12:07:52 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_nod(t_nod *nod, t_set_obj *s)
{
	ft_set_vec3(s->position, &nod->obj->pos);
	ft_set_vec3(s->normal, &nod->obj->norm);
	ft_normalise(&nod->obj->norm);
	ft_set_mat(s->mat, nod->obj);
	nod->obj->get_normal = &normal_plan;
	nod->obj->get_inters = &inters_plan;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	nod->obj_col->neg = 1;
}

int			ft_set_plane(char *plane, t_env *e, t_nod *prnt)
{
	t_set_obj	s;
	t_nod		nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((s.position = ft_get_inner(plane, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: plane require a <position> subobject.\n");
	if ((s.normal = ft_get_inner(plane, "normal", NULL, NULL)) == NULL)
		ft_error_exit("Error: plane require a <normal> subobject.\n");
	if ((s.mat = ft_get_inner(plane, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: plane require a material subobject.\n");
	(s.speed = ft_get_inner(plane, "speed", NULL, NULL)) == NULL ?
		(void)(nod.obj->speed = (t_vec3){0, 0, 0}) :
		ft_set_vec3(s.speed, &nod.obj->speed);
	ft_set_nod(&nod, &s);
	e ? ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod))) :
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&s.position);
	ft_strdel(&s.normal);
	ft_strdel(&s.mat);
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
