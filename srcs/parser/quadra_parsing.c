/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadra_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:30:47 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/02 11:46:16 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_nod(t_nod *nod, t_set_obj *s, char *quadra)
{
	ft_set_vec3(s->position, &nod->obj->pos);
	ft_set_vec3(s->rotation, &nod->obj->rot);
	ft_set_equ(s->equ, nod->obj);
	nod->obj->rayon = ft_atod(s->radius);
	ft_set_mat(s->mat, nod->obj);
	nod->obj->get_normal = &normal_quadra;
	nod->obj->get_inters = &inters_quadra;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	(s->speed = ft_get_inner(quadra, "speed", NULL, NULL)) == NULL ?
		(void)(nod->obj->speed = (t_vec3){0, 0, 0}) :
		ft_set_vec3(s->speed, &nod->obj->speed);
}

void		ft_set_quadra(char *quadra, t_env *e, t_nod *prnt)
{
	t_set_obj	s;
	t_nod		nod;

	if ((nod.obj = (t_obj *)malloc(sizeof(t_obj))) == NULL)
		ft_error_exit("Error: Cannot allocate memory.\n");
	if ((s.position = ft_get_inner(quadra, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: quadra require a position subobject.\n");
	if ((s.rotation = ft_get_inner(quadra, "rotation", NULL, NULL)) == NULL)
		ft_error_exit("error: camera require an angle subobject.\n");
	if ((s.equ = ft_get_inner(quadra, "equ", NULL, NULL)) == NULL)
		ft_error_exit("error: camera require an angle subobject.\n");
	if ((s.radius = ft_get_inner(quadra, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: quadra require a radius subobject.\n");
	if ((s.mat = ft_get_inner(quadra, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: quadra require a color subobject.\n");
	ft_set_nod(&nod, &s, quadra);
	e ? ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod))) :
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&s.position);
	ft_strdel(&s.radius);
	ft_strdel(&s.equ);
	ft_strdel(&s.rotation);
	ft_strdel(&s.mat);
	ft_strdel(&s.speed);
}

int			ft_get_quadras(char *objects, size_t len, t_env *e)
{
	char	*quadra;
	int		pos;

	pos = 0;
	while ((quadra = ft_get_inner(objects, "quadra", &pos, NULL)) != NULL)
	{
		ft_set_quadra(quadra, e, NULL);
		ft_strdel(&quadra);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
