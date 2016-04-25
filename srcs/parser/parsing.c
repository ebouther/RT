/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:36:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/25 16:54:59 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*ft_get_inner(char *str, char *obj)
{
	char	*obj_start_tag;
	char	*obj_end_tag;
	char	*ptr;
	char	*ptr2;
	size_t	len;
	char	*ret;

	ptr = NULL;
	ptr2 = NULL;
	obj_start_tag = ft_strjoin_free(ft_strdup("<"),
		ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	obj_end_tag = ft_strjoin_free(ft_strdup("</"),
		ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	len = ft_strlen(obj_start_tag);
	if ((ptr = ft_strstr(str, obj_start_tag)) != NULL
		&& (ptr2 = ft_strstr(str, obj_end_tag)) != NULL)
	{
		if ((ret = malloc(sizeof(char) * (ptr2 - (ptr + len) + 1))) == NULL)
			exit(-1);
		ft_strncpy(ret, ptr + len + 1,	ptr2 - (ptr + len + 1));
		ret[ptr2 - (ptr + len + 1)] = '\0';
		return (ret);
	}
	return (NULL);
}

int			ft_set_vec3(char *obj, t_vec3 *vec3)
{
	char	*x;
	char	*y;
	char	*z;

	if ((x = ft_get_inner(obj, "x")) == NULL
		|| (y = ft_get_inner(obj, "y")) == NULL
		|| (z = ft_get_inner(obj, "z")) == NULL)
	{
		ft_putstr("Error: ");
		ft_putstr(obj);
		ft_putstr(" require x, y and z subobjects.\n");
		exit(-1);
	}
	*vec3 = (t_vec3){ft_atod(x), ft_atod(y), ft_atod(z)};
	return (0);
}

int			ft_set_color(char *obj, t_color *col)
{
	char	*r;
	char	*g;
	char	*b;

	if ((r = ft_get_inner(obj, "r")) == NULL
		|| (g = ft_get_inner(obj, "g")) == NULL
		|| (b = ft_get_inner(obj, "b")) == NULL)
	{
		ft_putstr("Error: ");
		ft_putstr(obj);
		ft_putstr(" require r, b and b subobjects.\n");
		exit(-1);
	}
	*col = (t_color){ft_atod(r), ft_atod(g), ft_atod(b)};
	return (0);
}


static int		ft_set_lights(char *lights, t_env *e)
{
	char	*light;
	char	*position;
	char	*intensity;
	char	*color;
	t_light	light_obj;

	if ((light = ft_get_inner(lights, "light")) == NULL)
		ft_error_exit("Error: lights require light subobject.\n");
	if ((position = ft_get_inner(light, "position")) == NULL)
		ft_error_exit("Error: light require a position subobject.\n");
	if ((color = ft_get_inner(light, "color")) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	if ((intensity = ft_get_inner(light, "intensity")) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	ft_set_vec3(position, &light_obj.pos);
	ft_set_color(color, &light_obj.col);
	light_obj.k = ft_atod(intensity);
	ft_lstadd(&e->light, ft_lstnew((void *)&light_obj, sizeof(t_light)));
	return (0);
}

static int		ft_set_sphere(char *sphere, t_env *e)
{
	char	*position;
	char	*radius;
	char	*color;
	t_obj	sphere_obj;

	if ((position = ft_get_inner(sphere, "position")) == NULL)
		ft_error_exit("Error: sphere require a position subobject.\n");
	if ((radius = ft_get_inner(sphere, "radius")) == NULL)
		ft_error_exit("Error: sphere require a radius subobject.\n");
	if ((color = ft_get_inner(sphere, "color")) == NULL)
		ft_error_exit("Error: sphere require a color subobject.\n");
	ft_set_vec3(position, &sphere_obj.pos);
	sphere_obj.rayon = ft_atod(radius);
	ft_set_color(color, &sphere_obj.mat.col);
	sphere_obj.mat.brim = 0.5;
	sphere_obj.mat.ambiante = 1;

	sphere_obj.get_normal = &normal_sphere;
	sphere_obj.get_inters = &inters_sphere;
	ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_obj)));
	return (0);
}

static int		ft_set_cylinder(char *cylinder, t_env *e)
{
	char	*position;
	char	*direction;
	char	*radius;
	char	*color;
	t_obj	cylinder_obj;

	if ((position = ft_get_inner(cylinder, "position")) == NULL)
		ft_error_exit("Error: cylinder require a position subobject.\n");
	if ((radius = ft_get_inner(cylinder, "radius")) == NULL)
		ft_error_exit("Error: cylinder require a radius subobject.\n");
	if ((color = ft_get_inner(cylinder, "color")) == NULL)
		ft_error_exit("Error: cylinder require a color subobject.\n");
	if ((direction = ft_get_inner(cylinder, "direction")) == NULL)
		ft_error_exit("Error: cylinder require a direction subobject.\n");
	ft_set_vec3(position, &cylinder_obj.pos);
	ft_set_vec3(direction, &cylinder_obj.dir);
	cylinder_obj.rayon = ft_atod(radius);
	ft_set_color(color, &cylinder_obj.mat.col);
	cylinder_obj.mat.brim = 0.5;
	cylinder_obj.mat.ambiante = 1;

	cylinder_obj.get_normal = &normal_cyl;
	cylinder_obj.get_inters = &inters_cyl;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cylinder_obj, sizeof(t_obj)));
	return (0);
}

static int				ft_set_objects(char *objects, t_env *e)
{
	char	*sphere;
	char	*cylinder;

	if ((sphere = ft_get_inner(objects, "sphere")) != NULL)
		ft_set_sphere(sphere, e);
	if ((cylinder = ft_get_inner(objects, "cylinder")) != NULL)
		ft_set_cylinder(cylinder, e);
	return (0);
}

int				ft_parse_scene(char *file, t_env *e)
{
	char	*scene;
	char	*camera;
	char	*lights;
	char	*objects;

	if ((scene = ft_get_inner(file, "scene")) == NULL)
		ft_error_exit("Add a <scene> object to your scene.\n");
	if ((camera = ft_get_inner(scene, "camera")) == NULL)
		ft_error_exit("Error: add a camera to your scene.\n");
	if ((lights = ft_get_inner(scene, "lights")) == NULL)
		ft_putstr("There are no lights in your scene file.\n");
	if ((objects = ft_get_inner(scene, "objects")) == NULL)
		ft_putstr("There are no objects in your scene file.\n");
	ft_set_camera(camera, e);
	ft_set_lights(lights, e);
	ft_set_objects(objects, e);
	return (0);
}
