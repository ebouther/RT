/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:11:08 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/31 10:02:57 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_light2(t_light_parser *p, t_light *light_obj)
{
	light_obj->nb_light = ft_atod(p->nb_light);
	light_obj->dist_light = ft_atod(p->dist_light);
	ft_set_vec3(p->position, &light_obj->pos);
	ft_set_color(p->color, &light_obj->col);
	light_obj->k = ft_atod(p->intensity);
}

static int	ft_set_light(char *light, t_env *e)
{
	t_light_parser	p;
	t_light			light_obj;

	if ((p.position = ft_get_inner(light, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: light require a position subobject.\n");
	if ((p.color = ft_get_inner(light, "color", NULL, NULL)) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	if ((p.intensity = ft_get_inner(light, "intensity", NULL, NULL)) == NULL)
		ft_error_exit("Error: light require a color subobject.\n");
	if ((p.dist = ft_get_inner(light, "dir", NULL, NULL)) == NULL)
		ft_bzero(&light_obj.dir, sizeof(t_vec3));
	else
		ft_set_vec3(p.dist, &light_obj.dir);
	if ((p.nb_light = ft_get_inner(light, "nb_light", NULL, NULL)) == NULL)
		ft_error_exit("Error: light require a nb_light subobject.\n");
	if ((p.dist_light = ft_get_inner(light, "dist_light", NULL, NULL)) == NULL)
		ft_error_exit("Error: light require a dist_light subobject.\n");
	ft_set_light2(&p, &light_obj);
	ft_lstadd(&e->light, ft_lstnew((void *)&light_obj, sizeof(t_light)));
	ft_strdel(&p.position);
	ft_strdel(&p.intensity);
	ft_strdel(&p.color);
	return (0);
}

int			ft_get_lights(char *lights, size_t len, t_env *e)
{
	char	*light;
	int		pos;

	pos = 0;
	while ((light = ft_get_inner(lights, "light", &pos, NULL)) != NULL)
	{
		ft_set_light(light, e);
		ft_strdel(&light);
		if ((int)len - pos < 0)
			break ;
		lights += pos;
	}
	return (0);
}
