/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:57:32 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/16 17:29:35 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include <stdio.h>
void		ft_set_noise(char *perlin, t_obj *obj)
{
	char	*value;
	double	xy_period;
	double	turb_power;
	double	turb_size;

	xy_period = ((value = ft_get_inner(perlin, "ring_nb", NULL)) == NULL)
		? 12.0 : ft_atod(value);
	free(value);
	turb_power = ((value = ft_get_inner(perlin, "turb_power", NULL)) == NULL)
		? 0.1 : ft_atod(value);
	free(value);
	turb_size = ((value = ft_get_inner(perlin, "turb_size", NULL)) == NULL)
		? 32.0 : ft_atod(value);
	free(value);
	if ((value = ft_get_inner(perlin, "wood", NULL)) != NULL)
	{
		obj->mat.tex.buf = gen_wood(12.0, 0.1, 32.0);
	//	for (int i = 0; i < NOISE_HEIGHT * NOISE_WIDTH; i++)
	//		printf("%#x ", ((unsigned int *)obj->mat.tex.buf)[i]);
		obj->mat.tex.height1 = NOISE_HEIGHT;
		obj->mat.tex.width1 = NOISE_WIDTH;
	}
	free(value);
	/*if ((value = ft_get_inner(perlin, "noise", NULL)) != NULL)
	{
		
	}
	free(value);*/
}

void		ft_set_tex(char *tex, t_obj *obj)
{
	char	*value;

	obj->mat.tex.tex = ((value = ft_get_inner(tex, "path", NULL)) == NULL)
		? NULL : ft_strdup(value);
	free(value);

	(value = ft_get_inner(tex, "perlin", NULL)) == NULL ?
	obj->mat.tex.buf = NULL	: ft_set_noise(value, obj);
	free(value);
	
	obj->mat.tex.height = ((value = ft_get_inner(tex, "height", NULL)) == NULL)
		? 20 : ft_atoi(value); //change default values
	free(value);
	
	obj->mat.tex.width = ((value = ft_get_inner(tex, "width", NULL)) == NULL)
		? 20 : ft_atoi(value); //change default values
	free(value);

	obj->mat.tex.off_x	= ((value = ft_get_inner(tex, "offset_x", NULL)) == NULL)
		? 0 : ft_atod(value);
	free(value);

	obj->mat.tex.off_y	= ((value = ft_get_inner(tex, "offset_y", NULL)) == NULL)
		? 0 : ft_atod(value);
	free(value);
}

void		ft_set_mat(char *mat, t_obj *obj)
{
	char	*value;

	obj->mat.tex.buf = NULL;
	if ((value = ft_get_inner(mat, "color", NULL)) == NULL)
		ft_error_exit("Error: object require a color subobject.\n");
	ft_set_color(value, &obj->mat.col);
	free(value);
	obj->mat.brim = ((value = ft_get_inner(mat, "brim", NULL)) == NULL)
		? 0 : ft_atod(value);
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
	
	obj->mat.grid = ((value = ft_get_inner(mat, "grid", NULL)) == NULL)
		? FALSE : TRUE;
	free(value);

	(value = ft_get_inner(mat, "texture", NULL)) == NULL ?
	obj->mat.tex.tex = NULL	: ft_set_tex(value, obj);
	free(value);

	obj->mat.opac = ((value = ft_get_inner(mat, "opac", NULL)) == NULL)
		? 1 - obj->mat.refl - obj->mat.refr : ft_atod(value);
	free(value);
}
