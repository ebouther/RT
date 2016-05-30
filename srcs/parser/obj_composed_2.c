/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_composed_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:15:55 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/30 16:16:06 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_rot_cam(double angle, t_vec3 axe, t_obj *obj, t_vec3 rep[3])
{
	ft_rot_vec(angle, axe, &rep[0]);
	ft_rot_vec(angle, axe, &rep[1]);
	ft_rot_vec(angle, axe, &rep[2]);
	ft_rot_vec(angle, axe, &obj->dir);
	ft_rot_vec(angle, axe, &obj->dir2);
	ft_rot_vec(angle, axe, &obj->dir3);
	ft_rot_vec(angle, axe, &obj->norm);
}

static void	ft_rot_obj(t_obj *obj, t_vec3 rot)
{
	t_vec3 rep[3];

	rep[0].x = 0;
	rep[0].y = 1.0;
	rep[0].z = 0;
	rep[1].x = 1.0;
	rep[1].y = 0;
	rep[1].z = 0;
	rep[2].x = 0;
	rep[2].y = 0;
	rep[2].z = 1.0;
	ft_rot_cam(rot.x, rep[0], obj, rep);
	ft_rot_cam(rot.y, rep[1], obj, rep);
	ft_rot_cam(rot.z, rep[2], obj, rep);
}

int			ft_get_cobj(char *objects, t_env *e)
{
	char	*content;
	int		pos;
	size_t	len;
	char	*unio;
	char	*inters;
	char	*sub;
	int		u;
	int		i;
	int		s;

	len = ft_strlen(objects);
	pos = 0;
	while ((content = ft_get_inner(objects, "obj_composed", &pos, NULL)) != NULL)
	{
		unio = ft_get_inner(content, "union", NULL, &u);
		inters = ft_get_inner(content, "inters", NULL, &i);
		sub = ft_get_inner(content, "sub", NULL, &s);
		if (i != -1 && (i < s || s == -1) && (i < u || u == -1))
			ft_get_inter(inters, e, NULL);
		else if (u != -1 && (u < s || s == -1) && (u < i || i == -1))
			ft_get_union(unio, e, NULL);
		else if (s != -1 && (s < i || i == -1) && (s < u || u == -1))
			ft_get_sub(sub, e, NULL);
		ft_strdel(&content);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}

void		ft_treecpy(t_nod **dest, t_nod *src, t_vec3 pos, t_vec3 rot)
{
	*dest = (t_nod *)malloc(sizeof(t_nod));
	if (src->op == empty)
	{
		(*dest)->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
		(*dest)->obj = (t_obj *)malloc(sizeof(t_obj));
		ft_memcpy((*dest)->obj, src->obj, sizeof(t_obj));
		if (rot.x || rot.y || rot.z)
			ft_rot_obj((*dest)->obj, rot);
		(*dest)->obj->pos = (t_vec3){pos.x + (*dest)->obj->pos.x, pos.y + (*dest)->obj->pos.y, pos.z + (*dest)->obj->pos.z};
		(*dest)->l = NULL;
		(*dest)->r = NULL;
		(*dest)->op = empty;
	}
	else
	{
		(*dest)->obj_col = NULL;
		(*dest)->obj = NULL;
		(*dest)->op = src->op;
		ft_treecpy(&(*dest)->l, src->l, pos, rot);
		ft_treecpy(&(*dest)->r, src->r, pos, rot);
	}
}

int			ft_getlst(char *content, t_env *e)
{
	char	*position;
	char	*rotation;
	char	*id;
	t_vec3	pos;
	t_vec3	rot;
	t_nod	*nod;
	t_list	*save;

	save = e->c_obj;
	if ((id = ft_get_inner(content, "id", NULL, NULL)) == NULL)
		ft_error_exit("Error: obj need an id subobject");
	position = ft_get_inner(content, "position", NULL, NULL);
	rotation = ft_get_inner(content, "rotation", NULL, NULL);
	nod = (t_nod *)malloc(sizeof(t_nod));
	nod->id = ft_atod(id);
	while (e->c_obj)
	{
		if (nod->id == ((t_nod *)e->c_obj->content)->id)
		{
			if (position)
				ft_set_vec3(position, &pos);
			else
				pos = (t_vec3){0, 0, 0};
			if (rotation)
				ft_set_vec3(rotation, &rot);
			else
				rot = (t_vec3){0, 0, 0};
			ft_treecpy(&nod, e->c_obj->content, pos, rot);
			ft_lstadd(&e->obj, ft_lstnew((void *)nod, sizeof(t_nod)));
			break;
		}
		e->c_obj = e->c_obj->next;
	}
	e->c_obj = save;
	return (0);
}

int			ft_get_objtolist(char *objects, size_t len, t_env *e)
{
	char	*content;
	int		pos;

	pos = 0;
	while ((content = ft_get_inner(objects, "obj", &pos, NULL)) != NULL)
	{
		ft_getlst(content, e);
		ft_strdel(&content);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
