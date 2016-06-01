/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadra_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:30:47 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/01 10:43:08 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_quadra(char *quadra, t_env *e, t_nod *prnt)
{
	char	*position;
	char	*radius;
	char	*equ;
	char	*rotation;
	char	*mat;
	char	*speed;
	t_nod	nod;

	nod.obj = (t_obj *)malloc(sizeof(t_obj));
	if ((position = ft_get_inner(quadra, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: quadra require a position subobject.\n");
	if ((rotation = ft_get_inner(quadra, "rotation", NULL, NULL)) == NULL)
		ft_error_exit("error: camera require an angle subobject.\n");
	if ((equ = ft_get_inner(quadra, "equ", NULL, NULL)) == NULL)
		ft_error_exit("error: camera require an angle subobject.\n");
	if ((radius = ft_get_inner(quadra, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: quadra require a radius subobject.\n");
	if ((mat = ft_get_inner(quadra, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: quadra require a color subobject.\n");
	if ((speed = ft_get_inner(quadra, "speed", NULL, NULL)) == NULL)
		nod.obj->speed = (t_vec3){0, 0, 0};
	else
		ft_set_vec3(speed, &nod.obj->speed);
	ft_set_vec3(position, &nod.obj->pos);
	ft_set_vec3(rotation, &nod.obj->rot);
	ft_set_equ(equ, nod.obj);
	nod.obj->rayon = ft_atod(radius);
	ft_set_mat(mat, nod.obj);
	nod.obj->get_normal = &normal_quadra;
	nod.obj->get_inters = &inters_quadra;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = empty;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&position);
	ft_strdel(&radius);
	ft_strdel(&equ);
	ft_strdel(&rotation);
	ft_strdel(&mat);
	ft_strdel(&speed);
	return (0);
}

int			ft_get_quadras(char *objects, size_t len, t_env *e)
{
	char	*quadra;
	int		pos;

	pos = 0;
	while ((quadra = ft_get_inner(objects, "quadra", &pos, NULL)) != NULL)
	{
		ft_set_quadra(quadra, e, NULL);
		ft_strdel(&quadra);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
