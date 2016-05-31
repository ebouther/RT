/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 15:38:57 by pboutin           #+#    #+#             */
/*   Updated: 2016/05/31 16:21:27 by ebouther         ###   ########.fr       */
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

void						ft_calc_filtre(t_color *filtre, t_list *lst)
{
	filtre->r *= ((t_nod *)(lst->content))->obj->mat.col.r
		* (1 - ((t_nod *)(lst->content))->obj->mat.opac);
	filtre->g *= ((t_nod *)(lst->content))->obj->mat.col.g
		* (1 - ((t_nod *)(lst->content))->obj->mat.opac);
	filtre->b *= ((t_nod *)(lst->content))->obj->mat.col.b
		* (1 - ((t_nod *)(lst->content))->obj->mat.opac);
}
