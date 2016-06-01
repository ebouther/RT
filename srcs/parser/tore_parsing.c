/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 09:30:55 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/01 12:02:31 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_nod(t_nod *nod, t_set_obj *s, char *tore)
{
	ft_set_vec3(s->position, &nod->obj->pos);
	ft_set_vec3(s->direction, &nod->obj->dir);
	ft_normalise(&nod->obj->dir);
	nod->obj->rayon = ft_atod(s->radius);
	nod->obj->get_normal = &normal_tore;
	nod->obj->get_inters = &inters_tore;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	(s->speed = ft_get_inner(tore, "speed", NULL, NULL)) == NULL ?
		(void)(nod->obj->speed = (t_vec3){0, 0, 0}) :
		ft_set_vec3(s->speed, &nod->obj->speed);
	ft_set_mat(s->mat, nod->obj);
	nod->obj->rayon2 = ft_atod(s->radius2);
	ft_strdel(&s->position);
	ft_strdel(&s->direction);
	ft_strdel(&s->radius);
}

void		ft_set_tore(char *tore, t_env *e, t_nod *prnt)
{
	t_set_obj	s;
	t_nod		nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((s.position = ft_get_inner(tore, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require a position subobject.\n");
	if ((s.radius = ft_get_inner(tore, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require 2 radius subobject.\n");
	if ((s.radius2 = ft_get_inner(tore, "radius2", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require 2 radius subobject.\n");
	if ((s.mat = ft_get_inner(tore, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require a color subobject.\n");
	if ((s.direction = ft_get_inner(tore, "direction", NULL, NULL)) == NULL)
		ft_error_exit("Error: tore require a direction subobject.\n");
	ft_set_nod(&nod, &s, tore);
	e ? ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod))) :
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&s.radius2);
	ft_strdel(&s.mat);
	ft_strdel(&s.speed);
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
