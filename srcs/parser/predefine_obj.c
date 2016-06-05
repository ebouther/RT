/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed_obj_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 19:04:32 by pboutin           #+#    #+#             */
/*   Updated: 2016/06/05 18:40:38 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

void        ft_rot_axey(double angle, t_vec3 *vec)
{
	double  x;

	x = vec->x;
	vec->x = vec->x * cos(angle) + vec->z * sin(angle);
	vec->z = -x * sin(angle) + vec->z * cos(angle);
}

static void	ft_init_sphere(t_nod	*sphere, t_c_tore tore2)
{
	sphere->obj = (t_obj *)malloc(sizeof(t_obj));
	sphere->obj->mat.brim = 1;
	sphere->obj->mat.refl = 0;
	sphere->obj->mat.refr = 0;
	sphere->obj->mat.opac = 1;
	sphere->obj->rayon = tore2.rayon2;
	sphere->obj->get_normal = &normal_sphere;
	sphere->obj->get_inters = &inters_sphere;
	sphere->obj->mat.tex.tex = NULL;
	sphere->obj->mat.col = tore2.col;
}

static void	ft_init_sphereh(t_nod *sphere, t_c_helice helice)
{
	sphere->obj = (t_obj *)malloc(sizeof(t_obj));
	sphere->obj->mat.brim = 1;
	sphere->obj->mat.refl = 0;
	sphere->obj->mat.refr = 0;
	sphere->obj->mat.opac = 1;
	sphere->obj->rayon = 0.8/*helice.rayon*/;
	sphere->obj->get_normal = &normal_sphere;
	sphere->obj->get_inters = &inters_sphere;
	sphere->obj->mat.tex.tex = NULL;
	sphere->obj->mat.col = helice.col;
}

int	ft_set_helice(char *tore, t_env *e, t_c_helice helice)
{
	t_nod	sphere_obj;
	t_nod	sphere2_obj;
	t_nod	*cube;
	t_nod	*cyl;
	t_nod	cyl_obj;
	float		t;
	float		i;
/*	float		j;
	float		k;*/
	
	t = 0;
	i = -35;
	(void)tore;
	(void)e;
	sphere_obj.op = empty;
	sphere_obj.r = NULL;
	sphere_obj.l = NULL;
	sphere2_obj.op = empty;
	sphere2_obj.r = NULL;
	sphere2_obj.l = NULL;
	//
	cyl_obj.op = inters;
	cyl_obj.obj = NULL;
	cyl = (t_nod *)malloc(sizeof(t_nod*));
	cyl->op = empty;
	cyl->op = empty;
	cyl->op = empty;
	cyl->obj = (t_obj *)malloc(sizeof(t_obj));
	cyl->obj->get_normal = &normal_cyl;
	cyl->obj->get_inters = &inters_cyl;
	cyl->obj->mat.tex.tex = NULL;
	cyl->obj->mat.col = helice.col;
	cyl->obj->mat.brim = 1;
	cyl->obj->mat.refl = 0;
	cyl->obj->mat.refr = 0;
	cyl->obj->mat.opac = 1;
	cyl->obj->rayon = 0.8/*helice.rayon*/;
	cyl->obj->pos.x = 0;
	cyl->obj->pos.y = 0;
	cyl->obj->pos.z = 0;
	cyl->obj->dir.x = 0;
	cyl->obj->dir.y = 1;
	cyl->obj->dir.z = 0;
	cube = (t_nod *)malloc(sizeof(t_nod));
	cube->op = empty;
	cube->op = empty;
	cube->op = empty;
	cube->obj = (t_obj *)malloc(sizeof(t_obj));
	cube->obj->get_normal = &normal_cube;
	cube->obj->get_inters = &inters_cube;
	cube->obj->mat.tex.tex = NULL;
	cube->obj->mat.brim = 1;
	cube->obj->mat.refl = 0;
	cube->obj->mat.refr = 0;
	cube->obj->mat.opac = 1;
	cube->obj->scale.x = 50;
	cube->obj->scale.y = 50;
	cube->obj->scale.z = 50;
	cube->obj->pos.x = 0;
	cube->obj->pos.y = 0;
	cube->obj->pos.z = 0;
	cube->obj->dir.x = 0;
	cube->obj->dir.y = 1;
	cube->obj->dir.z = 0;
	cube->obj->dir2.x = 1;
	cube->obj->dir2.y = 0;
	cube->obj->dir2.z = 0;
	cube->obj->dir3.x = 0;
	cube->obj->dir3.y = 0;
	cube->obj->dir3.z = 1;

	cyl_obj.r = cyl;
	cyl_obj.l = cube;
	ft_lstadd(&e->obj, ft_lstnew((void *)&cyl_obj, sizeof(t_nod)));
	printf("ok\n");
	while (t < 8 * M_PI)
	{
		ft_init_sphereh(&sphere_obj, helice);
		ft_init_sphereh(&sphere2_obj, helice);
		sphere_obj.obj->pos = (t_vec3){10 * cos(t) - 25.0, t * 5 - 55, 10 * sin(t) - 120};
		sphere2_obj.obj->pos = (t_vec3){10 * cos(t) - 25.0,  (t + 3) * 5 - 55, 10 * sin(t) - 120};
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_nod)));
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere2_obj, sizeof(t_nod)));
		t = t + 0.4;
	}
	t = 0;
/*	t = 0;
	sphere_obj.obj->mat.col.g = 0;
	sphere_obj.obj->mat.col.r = 0;
	sphere_obj.obj->mat.col.b = 1;
	while(i < 40)
	{
		j = ((i + 40) / 5);
		k = ((i + 55) / 5);

		t = 0;
		while (t < 1)
		{
			ft_init_sphereh(&sphere_obj, helice);
			sphere_obj.obj->pos = (t_vec3){(10 * cos(j) - 25.0) + ((10 * cos(k) - 25.0) - (10 * cos(j) - 25.0)) * t, i, (10 * sin(j) - 120) + ((10 * sin(k) - 120) - (10 * sin(j) - 120)) * t};
			ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_nod)));
			t = t + 0.2;
		}
		i = i + 2;
	}*/
/*	while (t < 4 * M_PI)
	{*/
	//	cyl_obj.pos = (t_vec3){/*-25.0*/20 * cos(t) - 15.0, /*0.0*/ t * 10 - 50, 20 * sin(t) - 110};
	//	cyl_obj.dir = (t_vec3){1, 0, 0};
	//	ft_lstadd(&e->obj, ft_lstnew((void *)&cyl_obj, sizeof(t_obj)));
	//	t = t + 0.05;
//	}
	return (0);
}

static int	ft_set_tore2(char *tore, t_env *e, t_c_tore tore2)
{
	float		t;
	t_vec3	vec;
	t_nod	sphere_obj;
	
	t = 0;
	(void)tore;
	(void)e;
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

int		ft_get_composed_objects(char *objects, size_t len, t_env *e)
{
	char		*tore;
	char		*helice;
	int			pos;
	t_c_tore	tore2;
	t_c_helice	helice2;
	char		*value;

	pos = 0;
	while ((helice = ft_get_inner(objects, "c_helice", &pos, NULL)) != NULL)
	{
		if ((value = ft_get_inner(objects, "position", &pos, NULL)) != NULL)
		{
			ft_set_vec3(value, &helice2.pos);
			free(value);
		}
		if ((value = ft_get_inner(objects, "direction", &pos, NULL)) != NULL)
		{
			ft_set_vec3(value, &helice2.dir);
			free(value);
		}
		if ((value = ft_get_inner(objects, "color", &pos, NULL)) != NULL)
		{
			ft_set_color(value, &helice2.col);
			free(value);
		}
		if ((value = ft_get_inner(objects, "iteration", &pos, NULL)) != NULL)
		{
			helice2.iter = ft_atod(value);
			free(value);
		}
		if ((value = ft_get_inner(objects, "radius", &pos, NULL)) != NULL)
		{
			helice2.rayon = ft_atod(value);
			free(value);
		}
		ft_set_helice(helice, e, helice2);
		ft_strdel(&helice);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	while ((tore = ft_get_inner(objects, "c_tore", &pos, NULL)) != NULL)
	{
		if ((value = ft_get_inner(objects, "position", &pos, NULL)) != NULL)
		{
			ft_set_vec3(value, &tore2.pos);
			free(value);
		}
		if ((value = ft_get_inner(objects, "direction", &pos, NULL)) != NULL)
		{
			ft_set_vec3(value, &tore2.dir);
			free(value);
		}
		if ((value = ft_get_inner(objects, "color", &pos, NULL)) != NULL)
		{
			ft_set_color(value, &tore2.col);
			free(value);
		}
		if ((value = ft_get_inner(objects, "radius", &pos, NULL)) != NULL)
		{
			tore2.rayon = ft_atod(value);
			free(value);
		}
		if ((value = ft_get_inner(objects, "radius2", &pos, NULL)) != NULL)
		{
			tore2.rayon2 = ft_atod(value);
			free(value);
		}
		if ((value = ft_get_inner(objects, "iteration", &pos, NULL)) != NULL)
		{
			tore2.iter = ft_atod(value);
			free(value);
		}
		ft_set_tore2(tore, e, tore2);
		ft_strdel(&tore);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
