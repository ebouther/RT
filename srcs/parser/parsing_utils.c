/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 10:53:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/02 10:53:54 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_vec3(char *obj, t_vec3 *vec3)
{
	char	*x;
	char	*y;
	char	*z;

	if ((x = ft_get_inner(obj, "x", NULL, NULL)) == NULL
			|| (y = ft_get_inner(obj, "y", NULL, NULL)) == NULL
			|| (z = ft_get_inner(obj, "z", NULL, NULL)) == NULL)
	{
		ft_putstr("Error: ");
		ft_putstr(obj);
		ft_putstr(" require x, y and z subobjects.\n");
		exit(-1);
	}
	*vec3 = (t_vec3){ft_atod(x), ft_atod(y), ft_atod(z)};
	ft_strdel(&x);
	ft_strdel(&y);
	ft_strdel(&z);
	return (0);
}

int			ft_set_color(char *obj, t_color *col)
{
	char	*r;
	char	*g;
	char	*b;

	if ((r = ft_get_inner(obj, "r", NULL, NULL)) == NULL
			|| (g = ft_get_inner(obj, "g", NULL, NULL)) == NULL
			|| (b = ft_get_inner(obj, "b", NULL, NULL)) == NULL)
	{
		ft_putstr("Error: ");
		ft_putstr(obj);
		ft_putstr(" require r, b and b subobjects.\n");
		exit(-1);
	}
	*col = (t_color){ft_atod(r), ft_atod(g), ft_atod(b)};
	ft_strdel(&r);
	ft_strdel(&g);
	ft_strdel(&b);
	return (0);
}
