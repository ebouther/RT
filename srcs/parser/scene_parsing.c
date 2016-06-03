/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 10:52:41 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/03 15:42:59 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_objects(char *objects, t_env *e)
{
	size_t	len;

	len = ft_strlen(objects);
	ft_get_composed_objects(objects, len, e);
	ft_get_composed_objects(objects, len, e);
	ft_get_spheres(objects, len, e);
	ft_get_cylinders(objects, len, e);
	ft_get_tores(objects, len, e);
	ft_get_quadras(objects, len, e);
	ft_get_pobjs(objects, len, e);
	ft_get_cones(objects, len, e);
	ft_get_planes(objects, len, e);
	ft_get_objtolist(objects, len, e);
	ft_get_cubes(objects, len, e);
	return (0);
}

static void	ft_free_all_dat_stuff(char **str[5])
{
	ft_strdel(str[0]);
	ft_strdel(str[1]);
	ft_strdel(str[2]);
	ft_strdel(str[3]);
	ft_strdel(str[4]);
}

void		ft_parse_scene(char *file, t_env *e)
{
	char	*scene;
	char	*camera;
	char	*lights;
	char	*objects;
	char	*config;

	ft_get_cobj(file, e);
	if ((scene = ft_get_inner(file, "scene", NULL, NULL)) == NULL)
		ft_error_exit(ERR_NO_SCENE);
	if ((camera = ft_get_inner(scene, "camera", NULL, NULL)) == NULL)
		ft_error_exit(ERR_NO_CAM);
	if ((config = ft_get_inner(scene, "config", NULL, NULL)) == NULL)
		ft_error_exit(ERR_NO_CONFIG);
	if ((objects = ft_get_inner(scene, "objects", NULL, NULL)) == NULL)
		ft_putstr("There are no objects in your scene file.\n");
	((lights = ft_get_inner(scene, "lights", NULL, NULL)) != NULL) ?
		ft_get_lights(lights, ft_strlen(lights), e) :
		ft_putstr("There are no lights in your scene file.\n");
	ft_set_config(config, e);
	ft_set_camera(camera, e);
	ft_set_objects(objects, e);
	ft_free_all_dat_stuff((char **[5]){&lights, &scene, &camera, &objects,
											&config});
}
