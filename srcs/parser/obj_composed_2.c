/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_composed_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:15:55 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/18 16:19:30 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_get_cobj(char *objects, char *op, t_env *e, int (*f)())
{
	char	*content;
	int		pos;
	size_t	len;

	len = ft_strlen(objects);
	pos = 0;
	while ((content = ft_get_inner(objects, op, &pos)) != NULL)
	{
		f(content, e, NULL);
		ft_strdel(&content);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}

void		ft_treecpy(t_nod **dest, t_nod *src, t_vec3 pos)
{
	*dest = (t_nod *)malloc(sizeof(t_nod));
	if (src->obj)
	{
		(*dest)->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
		(*dest)->obj = (t_obj *)malloc(sizeof(t_obj));
		ft_memcpy((*dest)->obj, src->obj, sizeof(t_obj));
		(*dest)->obj->pos = (t_vec3){pos.x + (*dest)->obj->pos.x, pos.y + (*dest)->obj->pos.y, pos.z + (*dest)->obj->pos.z};
		(*dest)->l = NULL;
		(*dest)->r = NULL;
		(*dest)->op = NULL;
	}
	else
	{
		(*dest)->obj_col = NULL;
		(*dest)->obj = NULL;
		(*dest)->op = src->op;
		ft_treecpy(&(*dest)->l, src->l, pos);
		ft_treecpy(&(*dest)->r, src->r, pos);
	}
}

int			ft_getlst(char *content, t_env *e)
{
	char	*position;
	char	*id;
	t_vec3	pos;
	t_nod	*nod;
	t_list	*save;

	save = e->c_obj;
	if ((id = ft_get_inner(content, "id", NULL)) == NULL)
		ft_error_exit("Error: obj need an id subobject");
	position = ft_get_inner(content, "position", NULL);
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
			ft_treecpy(&nod, e->c_obj->content, pos);
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
	while ((content = ft_get_inner(objects, "obj", &pos)) != NULL)
	{
		ft_getlst(content, e);
		ft_strdel(&content);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
