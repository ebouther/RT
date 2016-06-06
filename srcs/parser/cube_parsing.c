/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:41:05 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/05 22:43:17 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		ft_dir3(t_vec3 dir, t_vec3 dir2, t_vec3 *dir3)
{
	dir3->x = dir2.y * dir.z - dir2.z * dir.y;
	dir3->y = dir2.z * dir.x - dir2.x * dir.z;
	dir3->z = dir2.x * dir.y - dir2.y * dir.x;
	ft_normalise(dir3);
}

static void		ft_del_cube(t_set_obj p)
{
	ft_strdel(&p.position);
	ft_strdel(&p.direction);
	ft_strdel(&p.direction2);
	ft_strdel(&p.scale);
	ft_strdel(&p.mat);
	ft_strdel(&p.speed);
}

static void		ft_set_cube2(t_set_obj p, t_env *e, t_nod *nod, t_nod *prnt)
{
	if (scal(nod->obj->dir2, nod->obj->dir) != 0)
		ft_error_exit("Error: Non-orthogonal vectors.\n");
	ft_normalise(&nod->obj->dir);
	ft_normalise(&nod->obj->dir2);
	ft_set_vec3(p.position, &nod->obj->pos);
	ft_set_vec3(p.scale, &nod->obj->scale);
	ft_dir3(nod->obj->dir, nod->obj->dir2, &nod->obj->dir3);
	ft_set_mat(p.mat, nod->obj);
	nod->obj->get_normal = &normal_cube;
	nod->obj->get_inters = &inters_cube;
	nod->r = NULL;
	nod->l = NULL;
	nod->op = empty;
	nod->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, nod, sizeof(t_nod));
}

int				ft_set_cube(char *cube, t_env *e, t_nod *prnt)
{
	t_set_obj	p;
	t_nod		nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((p.position = ft_get_inner(cube, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: cube require a position subobject.\n");
	if ((p.mat = ft_get_inner(cube, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: cube require a material subobject.\n");
	if ((p.direction = ft_get_inner(cube, "direction", NULL, NULL)) == NULL)
		nod.obj->dir = (t_vec3){0, 0, 1};
	else
		ft_set_vec3(p.direction, &nod.obj->dir);
	if ((p.direction2 = ft_get_inner(cube, "direction2", NULL, NULL)) == NULL)
		nod.obj->dir2 = (t_vec3){0, 1, 0};
	else
		ft_set_vec3(p.direction2, &nod.obj->dir2);
	if ((p.scale = ft_get_inner(cube, "scale", NULL, NULL)) == NULL)
		ft_error_exit("Error: cube require a scale subobject.\n");
	if ((p.speed = ft_get_inner(cube, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(p.speed, &nod.obj->speed);
	ft_set_cube2(p, e, &nod, prnt);
	ft_del_cube(p);
	return (0);
}

int				ft_get_cubes(char *objects, size_t len, t_env *e)
{
	char	*cube;
	int		pos;

	pos = 0;
	while ((cube = ft_get_inner(objects, "cube", &pos, NULL)) != NULL)
	{
		ft_set_cube(cube, e, NULL);
		ft_strdel(&cube);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
