/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:11:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/26 18:01:03 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_set_light(char *light, t_env *e)
{
	char	*position;
	char	*intensity;
	char	*nb_light;
	char	*dist_light;
	char	*color;
	t_light	light_obj;

	if ((position = ft_get_inner(light, "position", NULL)) == NULL)
		ft_error_exit("Error: light require a position subobject.\n");
	if ((color = ft_get_inner(light, "color", NULL)) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	if ((intensity = ft_get_inner(light, "intensity", NULL)) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	if ((nb_light = ft_get_inner(light, "nb_light", NULL)) == NULL)
		ft_error_exit("Error: light require a nb_light subobject.\n");
	if ((dist_light = ft_get_inner(light, "dist_light", NULL)) == NULL)
		ft_error_exit("Error: light require a dist_light subobject.\n");
	light_obj.nb_light = ft_atod(nb_light);
	light_obj.dist_light = ft_atod(dist_light);
	ft_set_vec3(position, &light_obj.pos);
	ft_set_color(color, &light_obj.col);
	light_obj.k = ft_atod(intensity);
	ft_lstadd(&e->light, ft_lstnew((void *)&light_obj, sizeof(t_light)));
	ft_strdel(&position);
	ft_strdel(&intensity);
	ft_strdel(&color);
	return (0);
}

int			ft_get_lights(char *lights, size_t len, t_env *e)
{
	char	*light;
	int		pos;

	pos = 0;
	while ((light = ft_get_inner(lights, "light", &pos)) != NULL)
	{
		ft_set_light(light, e);
		ft_strdel(&light);
		if ((int)len - pos < 0)
			break ;
		lights += pos;
	}
	return (0);
}
