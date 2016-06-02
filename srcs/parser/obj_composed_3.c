/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_composed_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:25:20 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/02 11:27:49 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_treecpy(t_nod **dest, t_nod *src, t_tree_vec3 v)
{
	*dest = (t_nod *)malloc(sizeof(t_nod));
	if (src->op == empty)
	{
		(*dest)->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
		(*dest)->obj = (t_obj *)malloc(sizeof(t_obj));
		ft_memcpy((*dest)->obj, src->obj, sizeof(t_obj));
		if (v.rot.x || v.rot.y || v.rot.z)
			ft_rot_obj((*dest)->obj, v.rot);
		(*dest)->obj->pos = (t_vec3){v.pos.x + (*dest)->obj->pos.x, v.pos.y +
				(*dest)->obj->pos.y, v.pos.z + (*dest)->obj->pos.z};
		(*dest)->l = NULL;
		(*dest)->r = NULL;
		(*dest)->obj->speed = (t_vec3){v.speed.x, v.speed.y, v.speed.z};
		(*dest)->op = empty;
	}
	else
	{
		(*dest)->obj_col = NULL;
		(*dest)->obj = NULL;
		(*dest)->op = src->op;
		ft_treecpy(&(*dest)->l, src->l, v);
		ft_treecpy(&(*dest)->r, src->r, v);
	}
}

static void	ft_init_getlst(t_getlst *g, char *content)
{
	if ((g->id = ft_get_inner(content, "id", NULL, NULL)) == NULL)
		ft_error_exit("Error: obj need an id subobject");
	g->position = ft_get_inner(content, "position", NULL, NULL);
	g->rotation = ft_get_inner(content, "rotation", NULL, NULL);
	g->cspeed = ft_get_inner(content, "speed", NULL, NULL);
	if ((g->nod = (t_nod *)malloc(sizeof(t_nod))) == NULL)
		ft_error_exit("Error: Cannot allocate memory.\n");
	g->nod->id = ft_atod(g->id);
}

static void	ft_getlst(char *content, t_env *e)
{
	t_getlst	g;

	g.save = e->c_obj;
	ft_init_getlst(&g, content);
	while (e->c_obj)
	{
		if (g.nod->id == ((t_nod *)e->c_obj->content)->id)
		{
			g.position ? ft_set_vec3(g.position, &g.pos)
				: (void)(g.pos = (t_vec3){0, 0, 0});
			g.rotation ? ft_set_vec3(g.rotation, &g.rot)
				: (void)(g.rot = (t_vec3){0, 0, 0});
			g.cspeed ? ft_set_vec3(g.cspeed, &g.speed)
				: (void)(g.speed = (t_vec3){0, 0, 0});
			ft_treecpy(&g.nod, e->c_obj->content,
				(t_tree_vec3){g.pos, g.rot, g.speed});
			ft_lstadd(&e->obj, ft_lstnew((void *)g.nod, sizeof(t_nod)));
			break ;
		}
		e->c_obj = e->c_obj->next;
	}
	e->c_obj = g.save;
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
