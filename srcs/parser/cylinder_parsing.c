/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:45:04 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 11:48:05 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_node(char *position, char *direction, char *radius,
				t_nod *nod)
{
	ft_set_vec3(position, &nod->obj->pos);
	ft_set_vec3(direction, &nod->obj->dir);
	ft_normalise(&nod->obj->dir);
	nod->obj->rayon = ft_atod(radius);
	nod->obj->get_normal = &normal_cyl;
	nod->obj->get_inters = &inters_cyl;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&radius);
}

int			ft_set_cylinder(char *cylinder, t_env *e, t_nod *prnt)
{
	t_set_obj	s;
	t_nod		nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((s.position = ft_get_inner(cylinder, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: cylinder require a position subobject.\n");
	if ((s.radius = ft_get_inner(cylinder, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: cylinder require a radius subobject.\n");
	if ((s.mat = ft_get_inner(cylinder, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: cylinder require a material subobject.\n");
	if ((s.direction =
			ft_get_inner(cylinder, "direction", NULL, NULL)) == NULL)
		ft_error_exit("Error: cylinder require a direction subobject.\n");
	if ((s.speed = ft_get_inner(cylinder, "speed", NULL, NULL)) == NULL)
		s.speed = NULL;
	ft_set_mat(s.mat, nod.obj);
	s.speed ? ft_set_vec3(s.speed, &nod.obj->speed) :
		(void)(nod.obj->speed = (t_vec3){0, 0, 0});
	ft_set_node(s.position, s.direction, s.radius, &nod);
	e ? ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod))) :
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&s.mat);
	ft_strdel(&s.speed);
	return (0);
}

int			ft_get_cylinders(char *objects, size_t len, t_env *e)
{
	char	*cylinder;
	int		pos;

	pos = 0;
	while ((cylinder = ft_get_inner(objects, "cylinder", &pos, NULL)) != NULL)
	{
		ft_set_cylinder(cylinder, e, NULL);
		ft_strdel(&cylinder);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
