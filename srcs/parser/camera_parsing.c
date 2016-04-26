/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:31:14 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/26 14:24:15 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_rot_vec(double angle, t_vec3 axe, t_vec3 *vec)
{
	t_vec3 norm;

	norm.x = -axe.y * vec->z + axe.z * vec->y;
	norm.y = axe.x * vec->z - axe.z * vec->x;
	norm.z = -axe.x * vec->y + axe.y * vec->x;
	ft_normalise(&norm);

	vec->x = vec->x * cos(angle) + norm.x * sin(angle);
	vec->y = vec->y * cos(angle) + norm.y * sin(angle);
	vec->z = vec->z * cos(angle) + norm.z * sin(angle);
	ft_normalise(vec);
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

int			ft_set_camera(char *camera, t_env *e)
{
	char	*position;
	char	*angle;
	char	*fov;

	if ((position = ft_get_inner(camera, "position", NULL)) == NULL)
		ft_error_exit("error: camera require a position subobject.\n");
	if ((angle = ft_get_inner(camera, "angle", NULL)) == NULL)
		ft_error_exit("error: camera require an angle subobject.\n");
	if ((fov = ft_get_inner(camera, "fov", NULL)) == NULL)
		ft_error_exit("error: camera require a fov subobject.\n");
	ft_set_vec3(position, &(e->cam.pos));
	ft_set_vec3(angle, &(e->cam.angle));
	e->cam.distfo = WIDTH / (2 * tan(ft_atod(fov) * M_PI_2 / 180.0));
	ft_stock_cam2(&e->cam);
	ft_normalise(&e->cam.dir);
	ft_normalise(&e->cam.up);
	ft_normalise(&e->cam.right);
	ft_strdel(&position);
	ft_strdel(&angle);
	ft_strdel(&fov);
	return (0);
}
