/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:36:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/26 12:59:30 by ebouther         ###   ########.fr       */
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
	return (0);
}

static int		ft_set_lights(char *lights, t_env *e)
{
	char	*light;
	char	*position;
	char	*intensity;
	char	*color;
	t_light	light_obj;

	if ((light = ft_get_inner(lights, "light", NULL)) == NULL)
		ft_error_exit("Error: lights require light subobject.\n");
	if ((position = ft_get_inner(light, "position", NULL)) == NULL)
		ft_error_exit("Error: light require a position subobject.\n");
	if ((color = ft_get_inner(light, "color", NULL)) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	if ((intensity = ft_get_inner(light, "intensity", NULL)) == NULL)
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

	if ((position = ft_get_inner(sphere, "position", NULL)) == NULL)
		ft_error_exit("Error: sphere require a position subobject.\n");
	if ((radius = ft_get_inner(sphere, "radius", NULL)) == NULL)
		ft_error_exit("Error: sphere require a radius subobject.\n");
	if ((color = ft_get_inner(sphere, "color", NULL)) == NULL)
		ft_error_exit("Error: sphere require a color subobject.\n");
	ft_set_vec3(position, &sphere_obj.pos);
	sphere_obj.rayon = ft_atod(radius);
	ft_set_color(color, &sphere_obj.mat.col);

	//Temp
	sphere_obj.mat.brim = 0.5;
	sphere_obj.mat.ambiante = 0.2;

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

	if ((position = ft_get_inner(cylinder, "position", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a position subobject.\n");
	if ((radius = ft_get_inner(cylinder, "radius", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a radius subobject.\n");
	if ((color = ft_get_inner(cylinder, "color", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a color subobject.\n");
	if ((direction = ft_get_inner(cylinder, "direction", NULL)) == NULL)
		ft_error_exit("Error: cylinder require a direction subobject.\n");
	ft_set_vec3(position, &cylinder_obj.pos);
	ft_set_vec3(direction, &cylinder_obj.dir);
	cylinder_obj.rayon = ft_atod(radius);
	ft_set_color(color, &cylinder_obj.mat.col);
	
	//Temp
	cylinder_obj.mat.brim = 0.5;
	cylinder_obj.mat.ambiante = 0.2;

	cylinder_obj.get_normal = &normal_cyl;
	cylinder_obj.get_inters = &inters_cyl;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cylinder_obj, sizeof(t_obj)));
	return (0);
}

static int		ft_set_cone(char *cone, t_env *e)
{
	char	*position;
	char	*direction;
	char	*angle;
	char	*color;
	t_obj	cone_obj;

	if ((position = ft_get_inner(cone, "position", NULL)) == NULL)
		ft_error_exit("Error: cone require a position subobject.\n");
	if ((angle = ft_get_inner(cone, "angle", NULL)) == NULL)
		ft_error_exit("Error: cone require an angle subobject.\n");
	if ((color = ft_get_inner(cone, "color", NULL)) == NULL)
		ft_error_exit("Error: cone require a color subobject.\n");
	if ((direction = ft_get_inner(cone, "direction", NULL)) == NULL)
		ft_error_exit("Error: cone require a direction subobject.\n");
	ft_set_vec3(position, &cone_obj.pos);
	ft_set_vec3(direction, &cone_obj.dir);
	cone_obj.angle = ft_atod(angle) / 180 * M_PI;
	ft_set_color(color, &cone_obj.mat.col);
	
	//Temp
	cone_obj.mat.brim = 0.5;
	cone_obj.mat.ambiante = 0.2;

	cone_obj.get_normal = &normal_cone;
	cone_obj.get_inters = &inters_cone;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cone_obj, sizeof(t_obj)));
	return (0);
}

static int		ft_set_plane(char *plane, t_env *e)
{
	char	*position;
	char	*normal;
	char	*color;
	t_obj	plane_obj;

	if ((position = ft_get_inner(plane, "position", NULL)) == NULL)
		ft_error_exit("Error: plane require a <position> subobject.\n");
	if ((normal = ft_get_inner(plane, "normal", NULL)) == NULL)
		ft_error_exit("Error: plane require a <normal> subobject.\n");
	if ((color = ft_get_inner(plane, "color", NULL)) == NULL)
		ft_error_exit("Error: plane require a <color> subobject.\n");
	ft_set_vec3(position, &plane_obj.pos);
	ft_set_vec3(normal, &plane_obj.norm);
	ft_set_color(color, &plane_obj.mat.col);
	
	//Temp
	plane_obj.mat.brim = 0.5;
	plane_obj.mat.ambiante = 1;

	plane_obj.get_normal = &normal_plan;
	plane_obj.get_inters = &inters_plan;
	ft_lstadd(&e->obj, ft_lstnew((void *)&plane_obj, sizeof(t_obj)));
	return (0);
}

static int				ft_set_objects(char *objects, t_env *e)
{
	char	*start_ptr;
	char	*sphere;
	char	*cylinder;
	char	*cone;
	char	*plane;
	int		pos;
	size_t	len;

	pos = 0;
	len = ft_strlen(objects);
	start_ptr = objects;
	while ((sphere = ft_get_inner(objects, "sphere", &pos)) != NULL)
	{
		ft_set_sphere(sphere, e);
		ft_strdel(&sphere);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	objects = start_ptr;
	while ((cylinder = ft_get_inner(objects, "cylinder", &pos)) != NULL)
	{
		ft_set_cylinder(cylinder, e);
		ft_strdel(&cylinder);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	objects = start_ptr;
	while ((cone = ft_get_inner(objects, "cone", &pos)) != NULL)
	{
		ft_set_cone(cone, e);
		ft_strdel(&cone);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	objects = start_ptr;
	while ((plane = ft_get_inner(objects, "plane", &pos)) != NULL)
	{
		ft_set_plane(plane, e);
		ft_strdel(&plane);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
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
	if ((lights = ft_get_inner(scene, "lights", NULL)) == NULL)
		ft_putstr("There are no lights in your scene file.\n");
	if ((objects = ft_get_inner(scene, "objects", NULL)) == NULL)
		ft_putstr("There are no objects in your scene file.\n");
	ft_set_camera(camera, e);
	ft_set_lights(lights, e);
	ft_set_objects(objects, e);
	return (0);
}
