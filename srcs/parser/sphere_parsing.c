/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:47:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 17:53:22 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void	ft_del_sphere(t_set_obj p)
{
	ft_strdel(&p.position);
	ft_strdel(&p.speed);
	ft_strdel(&p.radius);
	ft_strdel(&p.mat);
}

static void	ft_set_sphere2(t_env *e, t_set_obj p, t_nod *nod, t_nod *prnt)
{
	ft_set_vec3(p.position, &nod->obj->pos);
	nod->obj->rayon = ft_atod(p.radius);
	ft_set_mat(p.mat, nod->obj);
	nod->obj->get_normal = &normal_sphere;
	nod->obj->get_inters = &inters_sphere;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, nod, sizeof(t_nod));
}

int			ft_set_sphere(char *sphere, t_env *e, t_nod *prnt)
{
	t_set_obj	p;
	t_nod		nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((p.position = ft_get_inner(sphere, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: sphere require a position subobject.\n");
	if ((p.radius = ft_get_inner(sphere, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: sphere require a radius subobject.\n");
	if ((p.mat = ft_get_inner(sphere, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: sphere require a material subobject.\n");
	if ((p.speed = ft_get_inner(sphere, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(p.speed, &nod.obj->speed);
	ft_set_sphere2(e, p, &nod, prnt);
	ft_del_sphere(p);
	return (0);
}

int			ft_get_spheres(char *objects, size_t len, t_env *e)
{
	char	*sphere;
	int		pos;

	pos = 0;
	while ((sphere = ft_get_inner(objects, "sphere", &pos, NULL)) != NULL)
	{
		ft_set_sphere(sphere, e, NULL);
		ft_strdel(&sphere);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
