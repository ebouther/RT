/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:47:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/15 10:57:40 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_set_sphere(char *sphere, t_env *e, t_nod *prnt)
{
	char	*position;
	char	*radius;
	char	*mat;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	nod.obj->mat.brim = 0.2;
	if ((position = ft_get_inner(sphere, "position", NULL)) == NULL)
		ft_error_exit("Error: sphere require a position subobject.\n");
	if ((radius = ft_get_inner(sphere, "radius", NULL)) == NULL)
		ft_error_exit("Error: sphere require a radius subobject.\n");
	if ((mat = ft_get_inner(sphere, "mat", NULL)) == NULL)
		ft_error_exit("Error: sphere require a material subobject.\n");
	ft_set_vec3(position, &nod.obj->pos);
	nod.obj->rayon = ft_atod(radius);
	ft_set_mat(mat, nod.obj);
	nod.obj->get_normal = &normal_sphere;
	nod.obj->get_inters = &inters_sphere;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = NULL;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	nod.obj_col->neg = 1;
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&position);
	ft_strdel(&radius);
	ft_strdel(&mat);
	return (0);
}

int			ft_get_spheres(char *objects, size_t len, t_env *e)
{
	char	*sphere;
	int		pos;

	pos = 0;
	while ((sphere = ft_get_inner(objects, "sphere", &pos)) != NULL)
	{
		ft_set_sphere(sphere, e, NULL);
		ft_strdel(&sphere);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
