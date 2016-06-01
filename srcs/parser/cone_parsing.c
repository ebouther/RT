/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:49:15 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 11:46:23 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_cone_2(char *angle, char *position, char *direction,
				t_nod *nod)
{
	ft_set_vec3(position, &nod->obj->pos);
	ft_set_vec3(direction, &nod->obj->dir);
	ft_normalise(&nod->obj->dir);
	nod->obj->angle = ft_atod(angle) / 180 * M_PI;
	nod->obj->get_normal = &normal_cone;
	nod->obj->get_inters = &inters_cone;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	if ((nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col))) == NULL)
		exit(-1);
	ft_strdel(&position);
	ft_strdel(&direction);
	ft_strdel(&angle);
}

void		ft_set_cone(char *cone, t_env *e, t_nod *prnt)
{
	t_set_obj	s;
	t_nod		nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((s.position = ft_get_inner(cone, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require a position subobject.\n");
	if ((s.angle = ft_get_inner(cone, "angle", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require an angle subobject.\n");
	if ((s.mat = ft_get_inner(cone, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require a material subobject.\n");
	if ((s.direction = ft_get_inner(cone, "direction", NULL, NULL)) == NULL)
		ft_error_exit("Error: cone require a direction subobject.\n");
	if ((s.speed = ft_get_inner(cone, "speed", NULL, NULL)) == NULL)
		s.speed = NULL;
	s.speed ? ft_set_vec3(s.speed, &nod.obj->speed) :
		(void)(nod.obj->speed = (t_vec3){0, 0, 0});
	ft_set_mat(s.mat, nod.obj);
	ft_set_cone_2(s.angle, s.position, s.direction, &nod);
	e ? ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod))) :
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&s.mat);
	ft_strdel(&s.speed);
}

int			ft_get_cones(char *objects, size_t len, t_env *e)
{
	char	*cone;
	int		pos;

	pos = 0;
	while ((cone = ft_get_inner(objects, "cone", &pos, NULL)) != NULL)
	{
		ft_set_cone(cone, e, NULL);
		ft_strdel(&cone);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
