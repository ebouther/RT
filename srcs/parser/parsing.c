/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:36:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/25 16:26:34 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char		*ft_get_inner(char *str, char *obj)
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

static int		ft_set_vec3(char *obj, t_vec3 *vec3)
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

static int		ft_set_color(char *obj, t_color *col)
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

/*static void	ft_stock_cam1(t_env *e, char *c, int i)
{
	if (i == 1)
		e->cam.pos.x = ft_atof(c);
	if (i == 2)
		e->cam.pos.y = ft_atof(c);
	if (i == 3)
		e->cam.pos.z = ft_atof(c);
	if (i == 4)
		e->cam.angle.x = (ft_atof(c) / 180 * M_PI);
	if (i == 5)
		e->cam.angle.y = (ft_atof(c) / 180 * M_PI);
	if (i == 6)
		e->cam.angle.z = (ft_atof(c) / 180 * M_PI);
	if (i == 7)
		e->cam.distfo = WIDTH / ( 2 * tan(ft_atof(c) * M_PI_2 / 180.0));
}*/

static void	ft_rot_vec(double angle, t_vec3 axe, t_vec3 *vec)
{
	t_vec3 norm;

	norm.x = -axe.y * vec->z + axe.z * vec->y;
	norm.y = axe.x * vec->z - axe.z * vec->x;
	norm.z = -axe.x * vec->y + axe.y * vec->x;
	ft_normalise(&norm);

	vec->x = vec->x * cos(angle) + norm.x * sin(angle);
	vec->y = vec->y * cos(angle) + norm.y * sin(angle);
	vec->z = vec->z * cos(angle) + norm.z * sin(angle);
	ft_normalise(vec);
}

static void	ft_rot_cam(double angle, t_vec3 axe, t_cam *cam)
{
	ft_rot_vec(angle, axe, &cam->right);
	ft_rot_vec(angle, axe, &cam->up);
	ft_rot_vec(angle, axe, &cam->dir);

}

static void	ft_stock_cam2(t_cam *cam)
{
		cam->up.x = 0;
		cam->up.y = 1.0;
		cam->up.z = 0;
		cam->right.x = 1.0;
		cam->right.y = 0;
		cam->right.z = 0;
		cam->dir.x = 0;
		cam->dir.y = 0;
		cam->dir.z = 1.0;
		ft_rot_cam(cam->angle.x, cam->right, cam);
		ft_rot_cam(cam->angle.y, cam->up, cam);
		ft_rot_cam(cam->angle.z, cam->dir, cam);
}


static int		ft_set_camera(char *camera, t_env *e)
{
	char	*position;
	char	*angle;
	char	*fov;

	if ((position = ft_get_inner(camera, "position")) == NULL)
	{
		ft_putstr("error: camera require a position subobject.\n");
		exit(-1);
	}
	if ((angle = ft_get_inner(camera, "angle")) == NULL)
	{
		ft_putstr("error: camera require an angle subobject.\n");
		exit(-1);
	}
	if ((fov = ft_get_inner(camera, "fov")) == NULL)
	{
		ft_putstr("error: camera require a fov subobject.\n");
		exit(-1);
	}
	ft_set_vec3(position, &(e->cam.pos));
	ft_set_vec3(angle, &(e->cam.angle));
	e->cam.distfo = WIDTH / (2 * tan(ft_atod(fov) * M_PI_2 / 180.0));
	ft_stock_cam2(&e->cam);
	ft_normalise(&e->cam.dir);
	ft_normalise(&e->cam.up);
	ft_normalise(&e->cam.right);
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
	{
		ft_putstr("Error: lights require light subobject.\n");
		exit(-1);
	}
	if ((position = ft_get_inner(light, "position")) == NULL)
	{
		ft_putstr("Error: light require a position subobject.\n");
		exit(-1);
	}
	if ((color = ft_get_inner(light, "color")) == NULL)
	{
		ft_putstr("Error: light require a color subobject.\n");
		exit(-1);
	}
	if ((intensity = ft_get_inner(light, "intensity")) == NULL)
	{
		ft_putstr("Error: light require a color subobject.\n");
		exit(-1);
	}
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
	{
		ft_putstr("Error: sphere require a position subobject.\n");
		exit(-1);
	}
	if ((radius = ft_get_inner(sphere, "radius")) == NULL)
	{
		ft_putstr("Error: sphere require a radius subobject.\n");
		exit(-1);
	}
	if ((color = ft_get_inner(sphere, "color")) == NULL)
	{
		ft_putstr("Error: sphere require a color subobject.\n");
		exit(-1);
	}
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

static int				ft_set_objects(char *objects, t_env *e)
{
	char	*sphere;

	if ((sphere = ft_get_inner(objects, "sphere")) != NULL)
		ft_set_sphere(sphere, e);
	return (0);
}

int				ft_parse_scene(char *file, t_env *e)
{
	char	*scene;
	char	*camera;
	char	*lights;
	char	*objects;

	if ((scene = ft_get_inner(file, "scene")) == NULL)
	{
		ft_putstr("Add a <scene> object to your scene.\n");
		exit (-1);
	}
	if ((camera = ft_get_inner(scene, "camera")) == NULL)
	{
		ft_putstr("Error: add a camera to your scene.\n");
		exit(-1);
	}
	if ((lights = ft_get_inner(scene, "lights")) == NULL)
		ft_putstr("There are no lights in your scene file.\n");
	if ((objects = ft_get_inner(scene, "objects")) == NULL)
		ft_putstr("There are no objects in your scene file.\n");
	ft_set_camera(camera, e);
	ft_set_lights(lights, e);
	ft_set_objects(objects, e);
	return (0);
}
