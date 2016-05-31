/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equ_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 15:03:18 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 10:05:18 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_set_equ(char *equ, t_obj *obj)
{
	char	*value;

	obj->equ.x1 =
		((value = ft_get_inner(equ, "x1", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->equ.x2 =
	((value = ft_get_inner(equ, "x2", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->equ.y1 =
		((value = ft_get_inner(equ, "y1", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->equ.y2 =
		((value = ft_get_inner(equ, "y2", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->equ.z1 =
		((value = ft_get_inner(equ, "z1", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->equ.z2 =
		((value = ft_get_inner(equ, "z2", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
	obj->equ.c =
		((value = ft_get_inner(equ, "c", NULL, NULL)) == NULL) ? 0 : ft_atod(value);
	free(value);
}
