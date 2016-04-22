/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:32:03 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/22 12:20:51 by jbelless         ###   ########.fr       */
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
		e->cam.angle.x = ft_atof(c);
	if (i == 5)
		e->cam.angle.y = ft_atof(c);
	if (i == 6)
		e->cam.angle.z = ft_atof(c);
	if (i == 7)
		e->cam.distfo = WIDTH / ( 2 * tan(ft_atof(c) * M_PI_2 / 180.0));
}

static void	ft_stock_cam2(t_cam *cam)
{
		cam->up.x = ;
		cam->up.y = ;
		cam->up.z = ;
		cam->right.x = ;
		cam->right.y = ;
		cam->right.z = ;
		cam->dir.x = ;
		cam->dir.y = ;
		cam->dir.z = ;
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
		}
		else
			c++;
	}
	ft_stock_cam2(&e->cam);
	ft_normalise(&e->cam.dir);
	ft_normalise(&e->cam.up);
	ft_normalise(&e->cam.right);
}
