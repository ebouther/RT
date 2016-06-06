/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predefine3_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:55:13 by pboutin           #+#    #+#             */
/*   Updated: 2016/06/06 18:44:42 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_init_nod(t_nod *sphere_obj, t_nod *sphere2_obj, t_nod *cyl_obj)
{
	sphere_obj->op = empty;
	sphere_obj->r = NULL;
	sphere_obj->l = NULL;
	sphere2_obj->op = empty;
	sphere2_obj->r = NULL;
	sphere2_obj->l = NULL;
	cyl_obj->op = inters;
	cyl_obj->obj = NULL;
}

void		ft_pos_sphere(t_nod *sphere_obj, t_nod *sphere2_obj,
		t_c_helice helice, float t)
{
	ft_init_sphereh(sphere_obj, helice);
	ft_init_sphereh(sphere2_obj, helice);
	sphere_obj->obj->pos = (t_vec3){helice.rayon2 * cos(t) - helice.pos.x, t *
		5 - helice.pos.y, helice.rayon2 * sin(t) - helice.pos.z};
	sphere2_obj->obj->pos = (t_vec3){helice.rayon2 * cos(t + M_PI) -
		helice.pos.x, t * 5 - helice.pos.y, helice.rayon2 * sin(t + M_PI) -
			helice.pos.z};
}

void		ft_set_cyl_obj(t_nod *cyl_obj, t_c_helice helice, float t)
{
	t_nod	*cube;
	t_nod	*cyl;

	cyl = (t_nod *)malloc(sizeof(t_nod));
	cube = (t_nod *)malloc(sizeof(t_nod));
	ft_init_cyl(cyl, cube, helice);
	ft_dir_cyl(cyl, cube, helice, t);
	cube->obj->scale.z = sqrt(pow(helice.rayon2 * cos(t) - helice.pos.x -
	((helice.rayon2 * cos(t) - helice.pos.x + helice.rayon2 * cos(t + 3) -
	helice.pos.x) / 2), 2) + pow(helice.rayon2 * sin(t) - helice.pos.z -
	((helice.rayon2 * sin(t) - helice.pos.z + helice.rayon2 * sin(t + 3) -
	helice.pos.z) / 2), 2)) * 2;
	cyl_obj->r = cyl;
	cyl_obj->l = cube;
}
