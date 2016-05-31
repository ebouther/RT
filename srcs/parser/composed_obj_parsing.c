/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   composed_obj_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 19:04:32 by pboutin           #+#    #+#             */
/*   Updated: 2016/05/31 16:02:09 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void        ft_rot_axex(double angle, t_vec3 *vec);
void        ft_rot_axez(double angle, t_vec3 *vec);
void        ft_rot_axey(double angle, t_vec3 *vec)
{
	double  x;

	x = vec->x;
	vec->x = vec->x * cos(angle) + vec->z * sin(angle);
	vec->z = -x * sin(angle) + vec->z * cos(angle);
}

int	ft_set_helice(char *tore, t_env *e)
{
	t_obj	sphere_obj;
	t_obj	cyl_obj;
	float		t;
	float		i;
	float		j;
	float		k;
	
	t = 0;
	i = -35;
	(void)tore;
	(void)e;
	sphere_obj.mat.brim = 1;
	sphere_obj.mat.refl = 0;
	sphere_obj.mat.refr = 0;
	sphere_obj.mat.opac = 1;
	sphere_obj.rayon = 0.5;
	sphere_obj.get_normal = &normal_sphere;
	sphere_obj.get_inters = &inters_sphere;
	sphere_obj.mat.tex.tex = NULL;
	sphere_obj.mat.col.g = 1;
	sphere_obj.mat.col.r = 0;
	sphere_obj.mat.col.b = 0;
	cyl_obj.mat.brim = 1;
	sphere_obj.mat.refl = 0;
	sphere_obj.mat.refr = 0;
	sphere_obj.mat.opac = 1;
	cyl_obj.rayon = 0.5;
	cyl_obj.get_normal = &normal_cyl;
	cyl_obj.get_inters = &inters_cyl;
	cyl_obj.mat.tex.tex = NULL;
	cyl_obj.mat.col.g = 255;
	cyl_obj.mat.col.r = 255;
	cyl_obj.mat.col.r = 0;
	while (t < 8 * M_PI)
	{
		sphere_obj.pos = (t_vec3){/*-25.0*/10 * cos(t) - 25.0, /*0.0*/ t * 5 - 55, 10 * sin(t) - 120};
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_obj)));
		t = t + 0.2;
	}
	t = 0;
	while (t < 8 * M_PI)
	{
		sphere_obj.pos = (t_vec3){/*-25.0*/10 * cos(t) - 25.0, /*0.0*/ t * 5 - 40, 10 * sin(t) - 120};
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_obj)));
		t = t + 0.2;
	}
	t = 0;
	sphere_obj.mat.col.g = 0;
	sphere_obj.mat.col.r = 0;
	sphere_obj.mat.col.b = 1;
	while(i < 40)
	{
		j = ((i + 40) / 5);
		k = ((i + 55) / 5);

		t = 0;
		while (t < 1)
		{
			sphere_obj.pos = (t_vec3){/*-25.0*/(10 * cos(j) - 25.0) + ((10 * cos(k) - 25.0) - (10 * cos(j) - 25.0)) * t, i, (10 * sin(j) - 120) + ((10 * sin(k) - 120) - (10 * sin(j) - 120)) * t};
			ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_obj)));
			t = t + 0.2;
		}
		i = i + 2;
	}
/*	while (t < 4 * M_PI)
	{*/
	//	cyl_obj.pos = (t_vec3){/*-25.0*/20 * cos(t) - 15.0, /*0.0*/ t * 10 - 50, 20 * sin(t) - 110};
	//	cyl_obj.dir = (t_vec3){1, 0, 0};
	//	ft_lstadd(&e->obj, ft_lstnew((void *)&cyl_obj, sizeof(t_obj)));
	//	t = t + 0.05;
//	}
	return (0);
}

#include "stdio.h"
static int	ft_set_tore2(char *tore, t_env *e, t_c_tore tore2)
{
	t_obj	sphere_obj;
	float		t;
	t_vec3	vec;
	
	t = 0;
	(void)tore;
	(void)e;
	sphere_obj.mat.brim = 1;
	sphere_obj.mat.refl = 0;
	sphere_obj.mat.refr = 0;
	sphere_obj.mat.opac = 1;
	sphere_obj.rayon = tore2.rayon2;
	sphere_obj.get_normal = &normal_sphere;
	sphere_obj.get_inters = &inters_sphere;
	sphere_obj.mat.tex.tex = NULL;
	sphere_obj.mat.col = tore2.col;
	printf("%f\n", tore2.iter);
	while (t < 2 * M_PI)
	{
		vec = (t_vec3){tore2.rayon * cos(t), tore2.rayon * sin(t), 0};
		ft_rot_axex(tore2.dir.x * M_PI / 180, &vec);
		ft_rot_axey(tore2.dir.y * M_PI / 180, &vec);
		ft_rot_axez(tore2.dir.z * M_PI / 180, &vec);
		vec.x = vec.x - tore2.pos.x;
		vec.y = vec.y - tore2.pos.y;
		vec.z = vec.z - tore2.pos.z;
		sphere_obj.pos = vec;
		ft_lstadd(&e->obj, ft_lstnew((void *)&sphere_obj, sizeof(t_obj)));
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
	char		*value;

	pos = 0;
	while ((helice = ft_get_inner(objects, "c_helice", &pos, NULL)) != NULL)
	{
		ft_set_helice(helice, e);
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
