/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 18:13:41 by ascholle          #+#    #+#             */
/*   Updated: 2016/04/27 11:43:08 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_set_config(char *config, t_env *e)
{
	char	*ambient;
	char	*filter;

	if ((ambient = ft_get_inner(config, "ambient", NULL)) == NULL)
		ft_putstr("There are no ambient light in your scene file.\n");
	if ((filter = ft_get_inner(config, "filter", NULL)) == NULL)
		ft_putstr("There are no filter in your scene file.\n");
	e->amb = ft_atod(ambient);
	if (ft_strstr(filter, "sepia"))
		e->color_m = 1;
	else if (ft_strstr(filter, "B&W"))
		e->color_m = 2;
	else
		e->color_m = 0;
	ft_strdel(&ambient);
	ft_strdel(&filter);
	return (0);
}
