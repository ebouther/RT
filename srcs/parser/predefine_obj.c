/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed_obj_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 19:04:32 by pboutin           #+#    #+#             */
/*   Updated: 2016/06/06 18:49:16 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_helice(t_env *e, t_c_helice helice)
{
	t_nod	sphere_obj;
	t_nod	sphere2_obj;
	t_nod	cyl_obj;
	float	t;

	t = 0;
	ft_init_nod(&sphere_obj, &sphere2_obj, &cyl_obj);
	while (t < 8 * M_PI)
	{
		ft_pos_sphere(&sphere_obj, &sphere2_obj, helice, t);
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_nod)));
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere2_obj, sizeof(t_nod)));
		t = t + (8 * M_PI) / helice.iter;
	}
	t = 0;
	while (t < 8 * M_PI)
	{
		ft_set_cyl_obj(&cyl_obj, helice, t);
		ft_lstadd(&e->obj, ft_lstnew((void *)&cyl_obj, sizeof(t_nod)));
		t = t + ((8 * M_PI) / helice.iter * 5);
	}
	return (0);
}

static int	ft_set_tore2(char *tore, t_env *e, t_c_tore tore2)
{
	float	t;
	t_vec3	vec;
	t_nod	sphere_obj;

	t = 0;
	(void)tore;
	sphere_obj.op = empty;
	sphere_obj.r = NULL;
	sphere_obj.l = NULL;
	while (t < 2 * M_PI)
	{
		ft_init_sphere(&sphere_obj, tore2);
		vec = (t_vec3){tore2.rayon * cos(t), tore2.rayon * sin(t), 0};
		ft_rot_axex(tore2.dir.x * M_PI / 180, &vec);
		ft_rot_axey(tore2.dir.y * M_PI / 180, &vec);
		ft_rot_axez(tore2.dir.z * M_PI / 180, &vec);
		vec.x = vec.x - tore2.pos.x;
		vec.y = vec.y - tore2.pos.y;
		vec.z = vec.z - tore2.pos.z;
		sphere_obj.obj->pos = vec;
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_nod)));
		t = t + (2 * M_PI / tore2.iter);
	}
	return (0);
}

void		norm_helice_composed_objects(char *objects, int *pos,
		t_c_helice *helice2)
{
	char	*value;

	if ((value = ft_get_inner(objects, "position", pos, NULL)) != NULL)
		ft_set_vec3(value, &helice2->pos);
	free(value);
	if ((value = ft_get_inner(objects, "direction", pos, NULL)) != NULL)
		ft_set_vec3(value, &helice2->dir);
	free(value);
	if ((value = ft_get_inner(objects, "color", pos, NULL)) != NULL)
		ft_set_color(value, &helice2->col);
	free(value);
	if ((value = ft_get_inner(objects, "iteration", pos, NULL)) != NULL)
		helice2->iter = ft_atod(value);
	free(value);
	if ((value = ft_get_inner(objects, "radius", pos, NULL)) != NULL)
		helice2->rayon = ft_atod(value);
	free(value);
	if ((value = ft_get_inner(objects, "radius2", pos, NULL)) != NULL)
		helice2->rayon2 = ft_atod(value);
	free(value);
}

void		norm_tore_composed_objects(char *objects, int *pos, t_c_tore *tore2)
{
	char		*value;

	if ((value = ft_get_inner(objects, "position", pos, NULL)) != NULL)
		ft_set_vec3(value, &tore2->pos);
	free(value);
	if ((value = ft_get_inner(objects, "direction", pos, NULL)) != NULL)
		ft_set_vec3(value, &tore2->dir);
	free(value);
	if ((value = ft_get_inner(objects, "color", pos, NULL)) != NULL)
		ft_set_color(value, &tore2->col);
	free(value);
	if ((value = ft_get_inner(objects, "radius", pos, NULL)) != NULL)
		tore2->rayon = ft_atod(value);
	free(value);
	if ((value = ft_get_inner(objects, "radius2", pos, NULL)) != NULL)
		tore2->rayon2 = ft_atod(value);
	free(value);
	if ((value = ft_get_inner(objects, "iteration", pos, NULL)) != NULL)
		tore2->iter = ft_atod(value);
	free(value);
}

int			ft_get_composed_objects(char *objects, size_t len, t_env *e)
{
	char		*tore;
	char		*helice;
	int			pos;
	t_c_tore	tore2;
	t_c_helice	helice2;

	while ((helice = ft_get_inner(objects, "c_helice", &pos, NULL)) != NULL)
	{
		norm_helice_composed_objects(helice, &pos, &helice2);
		ft_set_helice(e, helice2);
		ft_strdel(&helice);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	while ((tore = ft_get_inner(objects, "c_tore", &pos, NULL)) != NULL)
	{
		norm_tore_composed_objects(tore, &pos, &tore2);
		ft_set_tore2(tore, e, tore2);
		ft_strdel(&tore);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
