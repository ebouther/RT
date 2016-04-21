/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:32:03 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/21 14:00:43 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_stock_cam1(t_env *e, char *c, int i)
{
	if (i == 1)
		e->cam.pos.x = ft_atof(c);
	if (i == 2)
		e->cam.pos.y = ft_atof(c);
	if (i == 3)
		e->cam.pos.z = ft_atof(c);
	if (i == 4)
		e->cam.dir.x = ft_atof(c);
	if (i == 5)
		e->cam.dir.y = ft_atof(c);
	if (i == 6)
		e->cam.dir.z = ft_atof(c);
}

static void	ft_stock_cam2(t_env *e, char *c, int i)
{
	if (i == 7)
		e->cam.up.x = ft_atof(c);
	if (i == 8)
		e->cam.up.y = ft_atof(c);
	if (i == 9)
		e->cam.up.z = ft_atof(c);
	if (i == 10)
		e->cam.right.x = ft_atof(c);
	if (i == 11)
		e->cam.right.y = ft_atof(c);
	if (i == 12)
		e->cam.right.z = ft_atof(c);
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
	ft_normalise(&e->cam.dir);
	ft_normalise(&e->cam.up);
	ft_normalise(&e->cam.right);
}
