/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:13:41 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/31 12:41:49 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_config(char *config, t_env *e)
{
	char	*ambient;
	char	*filter;

	if ((ambient = ft_get_inner(config, "ambient", NULL, NULL)) == NULL)
		ft_putstr("There are no ambient light in your scene file.\n");
	if ((filter = ft_get_inner(config, "filter", NULL, NULL)) == NULL)
		ft_putstr("There are no filter in your scene file.\n");
	e->amb = ft_atod(ambient);
	if (filter != NULL && ft_strstr(filter, "sepia"))
		e->color_m = 1;
	else if (filter != NULL && ft_strstr(filter, "B&W"))
		e->color_m = 2;
	else if (filter != NULL && ft_strstr(filter, "3D"))
		e->color_m = 3;
	else
		e->color_m = 0;
	ft_strdel(&ambient);
	ft_strdel(&filter);
	return (0);
}
