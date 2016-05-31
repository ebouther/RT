/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 13:57:32 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/31 10:04:18 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_set_noise2(char *perlin, double *xy_period,
				double *turb_power, double *turb_size)
{
	char	*value;

	*xy_period =
((value = ft_get_inner(perlin, "ring_nb", NULL, NULL)) == NULL) ?
														12.0 : ft_atod(value);
	free(value);
	*turb_power =
((value = ft_get_inner(perlin, "turb_power", NULL, NULL)) == NULL) ?
														0.1 : ft_atod(value);
	free(value);
	*turb_size =
((value = ft_get_inner(perlin, "turb_size", NULL, NULL)) == NULL) ?
														32.0 : ft_atod(value);
	free(value);
}

void		ft_set_noise(char *perlin, t_obj *obj)
{
	char	*value;
	double	xy_period;
	double	turb_power;
	double	turb_size;

	ft_set_noise2(perlin, &xy_period, &turb_power, &turb_size);
	if ((value = ft_get_inner(perlin, "wood", NULL, NULL)) != NULL)
	{
		obj->mat.tex.buf = gen_wood(xy_period, turb_power, turb_size);
		obj->mat.tex.height1 = NOISE_HEIGHT;
		obj->mat.tex.width1 = NOISE_WIDTH;
	}
	free(value);
	if ((value = ft_get_inner(perlin, "noise", NULL, NULL)) != NULL)
	{
		obj->mat.tex.buf = gen_noise(turb_size);
		obj->mat.tex.height1 = NOISE_HEIGHT;
		obj->mat.tex.width1 = NOISE_WIDTH;
	}
	free(value);
}

void		ft_set_tex(char *tex, t_obj *obj)
{
	char	*value;

	obj->mat.tex.tex =
((value = ft_get_inner(tex, "path", NULL, NULL)) == NULL) ? NULL : ft_strdup(value);
	free(value);
	(value = ft_get_inner(tex, "perlin", NULL, NULL)) == NULL ?
obj->mat.tex.buf = NULL : ft_set_noise(value, obj);
	free(value);
	obj->mat.tex.height =
((value = ft_get_inner(tex, "height", NULL, NULL)) == NULL) ? -70 : ft_atoi(value);
	free(value);
	obj->mat.tex.width =
((value = ft_get_inner(tex, "width", NULL, NULL)) == NULL) ? 0 : ft_atoi(value);
	free(value);
	obj->mat.tex.off_x =
((value = ft_get_inner(tex, "offset_x", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->mat.tex.off_y =
((value = ft_get_inner(tex, "offset_y", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
}

static void	ft_set_mat2(char *mat, t_obj *obj)
{
	char	*value;

	obj->mat.refl =
((value = ft_get_inner(mat, "reflection", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->mat.grid =
((value = ft_get_inner(mat, "grid", NULL, NULL)) == NULL) ? FALSE : TRUE;
	free(value);
	(value = ft_get_inner(mat, "texture", NULL, NULL)) == NULL ?
	obj->mat.tex.tex = NULL : ft_set_tex(value, obj);
	free(value);
	obj->mat.opac =
((value = ft_get_inner(mat, "opac", NULL, NULL)) == NULL) ?
1 - obj->mat.refl - obj->mat.refr : ft_atod(value);
	free(value);
	obj->mat.waves =
((value = ft_get_inner(mat, "waves", NULL, NULL)) == NULL) ? FALSE : TRUE;
	free(value);
}

void		ft_set_mat(char *mat, t_obj *obj)
{
	char	*value;

	obj->mat.tex.buf = NULL;
	if ((value = ft_get_inner(mat, "color", NULL, NULL)) == NULL)
		ft_error_exit("Error: object require a color subobject.\n");
	ft_set_color(value, &obj->mat.col);
	free(value);
	obj->mat.brim =
((value = ft_get_inner(mat, "brim", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->mat.brip =
((value = ft_get_inner(mat, "brip", NULL, NULL)) == NULL) ? 0 : (char)ft_atoi(value);
	free(value);
	obj->mat.i_opt =
((value = ft_get_inner(mat, "indice opt", NULL, NULL)) == NULL) ? 1 : ft_atod(value);
	free(value);
	obj->mat.refr =
((value = ft_get_inner(mat, "refraction", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	ft_set_mat2(mat, obj);
}
