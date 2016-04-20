/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:32:03 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/10 14:40:22 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_cam1(t_env *e, char *c, int i)
{
	if (i == 1)
		e->cam.posx = ft_atof(c);
	if (i == 2)
		e->cam.posy = ft_atof(c);
	if (i == 3)
		e->cam.posz = ft_atof(c);
	if (i == 4)
		e->cam.dirx = ft_atof(c);
	if (i == 5)
		e->cam.diry = ft_atof(c);
	if (i == 6)
		e->cam.dirz = ft_atof(c);
}

static void	ft_stock_cam2(t_env *e, char *c, int i)
{
	if (i == 7)
		e->cam.upx = ft_atof(c);
	if (i == 8)
		e->cam.upy = ft_atof(c);
	if (i == 9)
		e->cam.upz = ft_atof(c);
	if (i == 10)
		e->cam.rightx = ft_atof(c);
	if (i == 11)
		e->cam.righty = ft_atof(c);
	if (i == 12)
		e->cam.rightz = ft_atof(c);
	if (i == 13)
		e->cam.distfo = ft_atof(c);
}

void		ft_stock_cam(t_env *e, char *line)
{
	int		i;
	char	*c;

	i = 0;
	c = line;
	while (*c != '}')
	{
		if (*c == '$')
		{
			c++;
			i++;
			ft_stock_cam1(e, c, i);
			ft_stock_cam2(e, c, i);
		}
		else
			c++;
	}
	ft_normalise(&e->cam.dirx, &e->cam.diry, &e->cam.dirz);
	ft_normalise(&e->cam.upx, &e->cam.upy, &e->cam.upz);
	ft_normalise(&e->cam.rightx, &e->cam.righty, &e->cam.rightz);
}
