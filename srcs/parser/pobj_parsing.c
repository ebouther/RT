/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pobj_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 10:28:22 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/01 17:56:07 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_pobj_del(t_set_obj p)
{
	ft_strdel(&p.position);
	ft_strdel(&p.path);
	ft_strdel(&p.radius);
	ft_strdel(&p.mat);
	ft_strdel(&p.speed);
}

static void	ft_set_pobj2(t_set_obj p, t_nod *nod)
{
	ft_set_vec3(p.position, &nod->obj->pos);
	nod->obj->rayon = ft_atod(p.radius);
	ft_set_mat(p.mat, nod->obj);
	ft_read_pobj(p.path, nod->obj);
	nod->obj->get_normal = &normal_pobj;
	nod->obj->get_inters = &inters_pobj;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
}

int			ft_set_pobj(char *pobj, t_env *e, t_nod *prnt)
{
	t_set_obj	p;
	t_nod		nod;

	nod.obj = (t_obj*)malloc(sizeof(t_obj));
	if ((p.position = ft_get_inner(pobj, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: pobj require a position subobject.\n");
	if ((p.path = ft_get_inner(pobj, "path", NULL, NULL)) == NULL)
		ft_error_exit("error: pobj require a path to the .obj file.\n");
	if ((p.radius = ft_get_inner(pobj, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: pobj require a radius subobject.\n");
	if ((p.mat = ft_get_inner(pobj, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: pobj require a material subobject.\n");
	if ((p.speed = ft_get_inner(pobj, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(p.speed, &nod.obj->speed);
	ft_set_pobj2(p, &nod);
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_pobj_del(p);
	return (0);
}

int			ft_get_pobjs(char *objects, size_t len, t_env *e)
{
	char	*pobj;
	int		pos;

	pos = 0;
	while ((pobj = ft_get_inner(objects, "pobj", &pos, NULL)) != NULL)
	{
		ft_set_pobj(pobj, e, NULL);
		ft_strdel(&pobj);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
