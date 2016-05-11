/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:57:32 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/11 17:06:47 by pboutin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_set_mat(char *mat, t_obj *obj)
{
	char	*value;

	if ((value = ft_get_inner(mat, "color", NULL)) == NULL)
		ft_error_exit("Error: object require a color subobject.\n");
	ft_set_color(value, &obj->mat.col);
	free(value);
	obj->mat.brim = ((value = ft_get_inner(mat, "brim", NULL)) == NULL)
		? 0: ft_atod(value);
	free(value);
	obj->mat.brip = ((value = ft_get_inner(mat, "brip", NULL)) == NULL)
		? 0 : (char)ft_atoi(value);
	free(value);
	obj->mat.i_opt = ((value = ft_get_inner(mat, "indice opt", NULL)) == NULL)
		? 1 : ft_atod(value);
	free(value);
	obj->mat.refr = ((value = ft_get_inner(mat, "refraction", NULL)) == NULL)
		? 0 : ft_atod(value);
	free(value);
	obj->mat.refl = ((value = ft_get_inner(mat, "reflection", NULL)) == NULL)
		? 0 : ft_atod(value);
	free(value);

	obj->mat.tex.tex = ((value = ft_get_inner(mat, "texture", NULL)) == NULL)
		? NULL : ft_strdup(value);
	free(value);
	
	obj->mat.tex.height = ((value = ft_get_inner(mat, "tex_height", NULL)) == NULL)
		? 0 : ft_atoi(value);
	free(value);
	
	obj->mat.tex.width = ((value = ft_get_inner(mat, "tex_width", NULL)) == NULL)
		? 0 : ft_atoi(value);
	free(value);

	obj->mat.tex.off_x	= ((value = ft_get_inner(mat, "offset_x", NULL)) == NULL)
		? 0 : ft_atod(value);
	free(value);

	obj->mat.tex.off_y	= ((value = ft_get_inner(mat, "offset_y", NULL)) == NULL)
		? 0 : ft_atod(value);
	free(value);

	obj->mat.opac = ((value = ft_get_inner(mat, "opac", NULL)) == NULL)
		? 1 - obj->mat.refl - obj->mat.refr : ft_atod(value);
	free(value);
}
