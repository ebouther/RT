/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:36:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/26 14:33:42 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*ft_get_inner(char *str, char *obj, int *end_tag)
{
	char	*obj_start_tag;
	char	*obj_end_tag;
	char	*ptr[2];
	size_t	len;
	char	*ret;

	obj_start_tag = ft_strjoin_free(ft_strdup("<"),
		ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	obj_end_tag = ft_strjoin_free(ft_strdup("</"),
		ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	len = ft_strlen(obj_start_tag);
	if ((ptr[0] = ft_strstr(str, obj_start_tag)) != NULL
		&& (ptr[1] = ft_strstr(str, obj_end_tag)) != NULL)
	{
		if (end_tag != NULL)
			*end_tag = (int)ptr[1] - (int)str + len + 1;
		if ((ret = malloc(ptr[1] - (ptr[0] + len) + 1)) == NULL)
			exit(-1);
		ft_strncpy(ret, ptr[0] + len + 1, ptr[1] - (ptr[0] + len + 1));
		ret[ptr[1] - (ptr[0] + len + 1)] = '\0';
		ft_strdel(&obj_start_tag);
		ft_strdel(&obj_end_tag);
		return (ret);
	}
	ft_strdel(&obj_start_tag);
	ft_strdel(&obj_end_tag);
	return (NULL);
}

int			ft_set_vec3(char *obj, t_vec3 *vec3)
{
	char	*x;
	char	*y;
	char	*z;

	if ((x = ft_get_inner(obj, "x", NULL)) == NULL
		|| (y = ft_get_inner(obj, "y", NULL)) == NULL
		|| (z = ft_get_inner(obj, "z", NULL)) == NULL)
	{
		ft_putstr("Error: ");
		ft_putstr(obj);
		ft_putstr(" require x, y and z subobjects.\n");
		exit(-1);
	}
	*vec3 = (t_vec3){ft_atod(x), ft_atod(y), ft_atod(z)};
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
	return (0);
}

int			ft_set_color(char *obj, t_color *col)
{
	char	*r;
	char	*g;
	char	*b;

	if ((r = ft_get_inner(obj, "r", NULL)) == NULL
		|| (g = ft_get_inner(obj, "g", NULL)) == NULL
		|| (b = ft_get_inner(obj, "b", NULL)) == NULL)
	{
		ft_putstr("Error: ");
		ft_putstr(obj);
		ft_putstr(" require r, b and b subobjects.\n");
		exit(-1);
	}
	*col = (t_color){ft_atod(r), ft_atod(g), ft_atod(b)};
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
	return (0);
}

static int				ft_set_objects(char *objects, t_env *e)
{
	size_t	len;

	len = ft_strlen(objects);
	ft_get_spheres(objects, len, e);
	ft_get_cylinders(objects, len, e);
	ft_get_cones(objects, len, e);
	ft_get_planes(objects, len, e);
	return (0);
}

int				ft_parse_scene(char *file, t_env *e)
{
	char	*scene;
	char	*camera;
	char	*lights;
	char	*objects;

	if ((scene = ft_get_inner(file, "scene", NULL)) == NULL)
		ft_error_exit("Add a <scene> object to your scene.\n");
	if ((camera = ft_get_inner(scene, "camera", NULL)) == NULL)
		ft_error_exit("Error: add a camera to your scene.\n");
	if ((lights = ft_get_inner(scene, "lights", NULL)) != NULL)
		ft_get_lights(lights, ft_strlen(lights), e);
	else
		ft_putstr("There are no lights in your scene file.\n");
	if ((objects = ft_get_inner(scene, "objects", NULL)) == NULL)
		ft_putstr("There are no objects in your scene file.\n");
	ft_set_camera(camera, e);
	ft_set_objects(objects, e);
	ft_strdel(&scene);
	ft_strdel(&camera);
	ft_strdel(&lights);
	ft_strdel(&objects);
	return (0);
}
