/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predefine2_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:51:19 by pboutin           #+#    #+#             */
/*   Updated: 2016/06/06 18:07:24 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_rot_axey(double angle, t_vec3 *vec)
{
	double	x;

	x = vec->x;
	vec->x = vec->x * cos(angle) + vec->z * sin(angle);
	vec->z = -x * sin(angle) + vec->z * cos(angle);
}

void		ft_init_sphere(t_nod *sphere, t_c_tore tore2)
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

void		ft_init_sphereh(t_nod *sphere, t_c_helice helice)
{
	sphere->obj = (t_obj *)malloc(sizeof(t_obj));
	sphere->obj->mat.brim = 1;
	sphere->obj->mat.refl = 0;
	sphere->obj->mat.refr = 0;
	sphere->obj->mat.opac = 1;
	sphere->obj->rayon = helice.rayon;
	sphere->obj->get_normal = &normal_sphere;
	sphere->obj->get_inters = &inters_sphere;
	sphere->obj->mat.tex.tex = NULL;
	sphere->obj->mat.col = helice.col;
}

void		ft_init_cyl(t_nod *cyl, t_nod *cube, t_c_helice helice)
{
	cyl->op = empty;
	cyl->l = NULL;
	cyl->r = NULL;
	cyl->obj = (t_obj *)malloc(sizeof(t_obj));
	cyl->obj->get_normal = &normal_cyl;
	cyl->obj->get_inters = &inters_cyl;
	cyl->obj->mat.tex.tex = NULL;
	cyl->obj->mat.col = helice.col;
	cyl->obj->mat.brim = 1;
	cyl->obj->mat.refl = 0;
	cyl->obj->mat.refr = 0;
	cyl->obj->mat.opac = 1;
	cyl->obj->rayon = helice.rayon;
	cube->op = empty;
	cube->r = NULL;
	cube->l = NULL;
	cube->obj = (t_obj *)malloc(sizeof(t_obj));
	cube->obj->get_normal = &normal_cube;
	cube->obj->get_inters = &inters_cube;
	cube->obj->mat.tex.tex = NULL;
	cube->obj->mat.brim = 1;
	cube->obj->mat.refl = 0;
	cube->obj->mat.refr = 0;
	cube->obj->mat.opac = 1;
}

void		ft_dir_cyl(t_nod *cyl, t_nod *cube, t_c_helice helice, int t)
{
	cyl->obj->pos =
				(t_vec3){-helice.pos.x, t * 5 - helice.pos.y, -helice.pos.z};
	cube->obj->pos = (t_vec3)
					{-helice.pos.x, t * 5 - helice.pos.y, -helice.pos.z};
	cyl->obj->dir.x = (helice.rayon2 * cos(t) - helice.pos.x) - (helice.rayon2
			* cos(t + M_PI) - helice.pos.x);
	cyl->obj->dir.y = 0;
	cyl->obj->dir.z = (helice.rayon2 * sin(t) - helice.pos.z) - (helice.rayon2
			* sin(t + M_PI) - helice.pos.z);
	ft_normalise(&cyl->obj->dir);
	ft_normalise(&cyl->obj->dir2);
	ft_normalise(&cyl->obj->dir3);
	cube->obj->dir.x = (helice.rayon2 * cos(t) - helice.pos.x) - (helice.rayon2
			* cos(t + M_PI) - helice.pos.x);
	cube->obj->dir.y = 0;
	cube->obj->dir.z = (helice.rayon2 * sin(t) - helice.pos.z) - (helice.rayon2
			* sin(t + M_PI) - helice.pos.z);
	cube->obj->dir2 = (t_vec3){0, 1, 0};
	cube->obj->dir2.z = 0;
	ft_normalise(&cube->obj->dir);
	ft_normalise(&cube->obj->dir2);
	ft_dir3(cube->obj->dir, cube->obj->dir2, &cube->obj->dir3);
	cube->obj->scale = (t_vec3){50, 50, 0};
}
