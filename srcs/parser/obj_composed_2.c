/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_composed_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:15:55 by ascholle          #+#    #+#             */
/*   Updated: 2016/06/02 11:27:46 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_rot_cam(double angle, t_vec3 axe, t_obj *obj, t_vec3 rep[3])
{
	ft_rot_vec(angle, axe, &rep[0]);
	ft_rot_vec(angle, axe, &rep[1]);
	ft_rot_vec(angle, axe, &rep[2]);
	ft_rot_vec(angle, axe, &obj->dir);
	ft_rot_vec(angle, axe, &obj->pos);
	ft_rot_vec(angle, axe, &obj->dir2);
	ft_rot_vec(angle, axe, &obj->dir3);
	ft_rot_vec(angle, axe, &obj->norm);
}

void		ft_rot_obj(t_obj *obj, t_vec3 rot)
{
	t_vec3 rep[3];

	rep[0].x = 1.0;
	rep[0].y = 0;
	rep[0].z = 0;
	rep[1].x = 0;
	rep[1].y = 1.0;
	rep[1].z = 0;
	rep[2].x = 0;
	rep[2].y = 0;
	rep[2].z = 1.0;
	ft_rot_cam(rot.x, rep[0], obj, rep);
	ft_rot_cam(rot.y, rep[1], obj, rep);
	ft_rot_cam(rot.z, rep[2], obj, rep);
}

int			ft_get_cobj(char *objects, t_env *e)
{
	t_get_cobj	g;

	g.len = ft_strlen(objects);
	g.pos = 0;
	while ((g.content =
			ft_get_inner(objects, "obj_composed", &g.pos, NULL)) != NULL)
	{
		g.unio = ft_get_inner(g.content, "union", NULL, &g.u);
		g.inters = ft_get_inner(g.content, "inters", NULL, &g.i);
		g.sub = ft_get_inner(g.content, "sub", NULL, &g.s);
		if (g.i != -1 && (g.i < g.s || g.s == -1) && (g.i < g.u || g.u == -1))
			ft_get_inter(g.inters, e, NULL);
		else if (g.u != -1 && (g.u < g.s
					|| g.s == -1) && (g.u < g.i || g.i == -1))
			ft_get_union(g.unio, e, NULL);
		else if (g.s != -1 && (g.s < g.i
					|| g.i == -1) && (g.s < g.u || g.u == -1))
			ft_get_sub(g.sub, e, NULL);
		ft_strdel(&g.content);
		if ((int)g.len - g.pos < 0)
			break ;
		objects += g.pos;
	}
	return (0);
}
