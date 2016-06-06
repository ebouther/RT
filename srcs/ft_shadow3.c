/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 15:38:57 by pboutin           #+#    #+#             */
/*   Updated: 2016/06/06 12:00:36 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_norm_ft_calc_final_col	ft_norm_ishadow(t_norm_ft_calc_final_col norm,
								t_env *e, t_obj *cur_obj, t_shadow s)
{
	norm.e = e;
	norm.cur_obj = cur_obj;
	norm.col = &s.col;
	norm.col_res = &s.col_res;
	norm.refl = s.refl;
	return (norm);
}

void						ft_calc_filtre(t_color *filtre, t_obj *obj)
{
	filtre->r *= obj->mat.col.r * (1 - obj->mat.opac);
	filtre->g *= obj->mat.col.g * (1 - obj->mat.opac);
	filtre->b *= obj->mat.col.b * (1 - obj->mat.opac);
}

int							ft_checkerboard(t_ray *ray, double t)
{
	t_vec3	pos;

	pos = (t_vec3){ray->dir.x * t + ray->pos.x, ray->dir.y * t + ray->pos.y,
		ray->dir.z * t + ray->pos.z};
	if ((int)pos.y <= 0)
		pos.y--;
	if ((int)pos.x <= 0)
		pos.x--;
	if ((((int)pos.x + (int)pos.y) / 2) % 2 == 0)
		return (1);
	return (0);
}
