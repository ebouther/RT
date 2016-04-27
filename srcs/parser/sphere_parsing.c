/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:47:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/26 18:07:32 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_sphere(char *sphere, t_env *e)
{
	char	*position;
	char	*radius;
	char	*color;
	t_obj	sphere_obj;

	sphere_obj.mat.brim = 0.2;
	if ((position = ft_get_inner(sphere, "position", NULL)) == NULL)
		ft_error_exit("Error: sphere require a position subobject.\n");
	if ((radius = ft_get_inner(sphere, "radius", NULL)) == NULL)
		ft_error_exit("Error: sphere require a radius subobject.\n");
	if ((color = ft_get_inner(sphere, "color", NULL)) == NULL)
		ft_error_exit("Error: sphere require a color subobject.\n");
	ft_set_vec3(position, &sphere_obj.pos);
	sphere_obj.rayon = ft_atod(radius);
	ft_set_color(color, &sphere_obj.mat.col);
	sphere_obj.get_normal = &normal_sphere;
	sphere_obj.get_inters = &inters_sphere;
	ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_obj)));
	return (0);
}

int			ft_get_spheres(char *objects, size_t len, t_env *e)
{
	char	*sphere;
	int		pos;

	pos = 0;
	while ((sphere = ft_get_inner(objects, "sphere", &pos)) != NULL)
	{
		ft_set_sphere(sphere, e);
		ft_strdel(&sphere);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
