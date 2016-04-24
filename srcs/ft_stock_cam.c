/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:32:03 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/24 16:44:26 by ascholle         ###   ########.fr       */
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
		e->cam.angle.x = (ft_atof(c) / 180 * M_PI);
	if (i == 5)
		e->cam.angle.y = (ft_atof(c) / 180 * M_PI);
	if (i == 6)
		e->cam.angle.z = (ft_atof(c) / 180 * M_PI);
	if (i == 7)
		e->cam.distfo = WIDTH / ( 2 * tan(ft_atof(c) * M_PI_2 / 180.0));
}

#include <stdio.h>

static void	ft_rot_vec(double angle, t_vec3 axe, t_vec3 *vec)
{
	t_vec3 norm;

	norm.x = -axe.y * vec->z + axe.z * vec->y;
	norm.y = axe.x * vec->z - axe.z * vec->x;
	norm.z = -axe.x * vec->y + axe.y * vec->x;
	printf("axe.x = %f, axe.y =  %f,axe.z =  %f\n", axe.x, axe.y, axe.z);
	printf("vec.x = %f, vec.y =  %f,vec.z =  %f\n", vec->x, vec->y, vec->z);
	printf("normx = %f, norm.y =  %f,norm.z =  %f\n", norm.x, norm.y, norm.z);
	ft_normalise(&norm);

	vec->x = vec->x * cos(angle) + norm.x * sin(angle);
	vec->y = vec->y * cos(angle) + norm.y * sin(angle);
	vec->z = vec->z * cos(angle) + norm.z * sin(angle);
	ft_normalise(vec);
	printf("vec.x = %f, vec.y =  %f,vec.z =  %f\n\n", vec->x, vec->y, vec->z);
}

static void	ft_rot_cam(double angle, t_vec3 axe, t_cam *cam)
{
	ft_rot_vec(angle, axe, &cam->right);
	ft_rot_vec(angle, axe, &cam->up);
	ft_rot_vec(angle, axe, &cam->dir);

}

static void	ft_stock_cam2(t_cam *cam)
{
		cam->up.x = 0;
		cam->up.y = 1.0;
		cam->up.z = 0;
		cam->right.x = 1.0;
		cam->right.y = 0;
		cam->right.z = 0;
		cam->dir.x = 0;
		cam->dir.y = 0;
		cam->dir.z = 1.0;
		ft_rot_cam(cam->angle.x, cam->right, cam);
		ft_rot_cam(cam->angle.y, cam->up, cam);
		ft_rot_cam(cam->angle.z, cam->dir, cam);
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
