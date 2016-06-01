/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:47:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 17:33:53 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void	ft_del_sphere(char **p)
{
	int i;

	i = 0;
	while (i < 4)
	{
		ft_strdel(&p[i]);
		i++;
	}
	ft_strdel(p);
}

static void	ft_set_sphere2(t_env *e, char **p, t_nod *nod, t_nod *prnt)
{
	ft_set_vec3(p[0], &nod->obj->pos);
	nod->obj->rayon = ft_atod(p[1]);
	ft_set_mat(p[2], nod->obj);
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
	char	**p;
	t_nod	nod;

	p = (char **)malloc(sizeof(char*) * 4);
	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((p[0] = ft_get_inner(sphere, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: sphere require a position subobject.\n");
	if ((p[1] = ft_get_inner(sphere, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: sphere require a radius subobject.\n");
	if ((p[2] = ft_get_inner(sphere, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: sphere require a material subobject.\n");
	if ((p[3] = ft_get_inner(sphere, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(p[3], &nod.obj->speed);
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
