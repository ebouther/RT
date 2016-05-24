/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 14:34:14 by pboutin           #+#    #+#             */
/*   Updated: 2016/05/24 14:51:34 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_color     ft_get_tex_color(int x, int y, t_obj *cur_obj)
{
	unsigned char   *c;
	t_color         ret;
	c = (unsigned char*)cur_obj->mat.tex.buf + (x) * 4 + (y * cur_obj->mat.tex.width1 * 4);
	ret.b = *c / 256.0;
	ret.g = *(c + 1) / 256.0;
	ret.r = *(c + 2) / 256.0;
	return(ret);
}

void        ft_rot_axeX(double angle, t_vec3 *vec)
{
	double  y;

	y = vec->y;
	vec->y = vec->y * cos(angle) - vec->z * sin(angle);
	vec->z = y * sin(angle) + vec->z * cos(angle);
}

void        ft_rot_axeZ(double angle, t_vec3 *vec)
{
	double  x;

	x = vec->x;
	vec->x = vec->x * cos(angle) - vec->y * sin(angle);
	vec->y = x * sin(angle) + vec->y * cos(angle);
}

void        ft_rot2(double rx, double rz, t_vec3 *vec)
{
	double  x;
	double  y;
	double  ry;

	ry = 0;
	x = vec->x;
	y = vec->y;
	vec->x = x * cos(ry) * cos(rz) - cos(ry) * sin(rz) * y + sin(ry) * vec->z;
	vec->y = x * (sin(rx) * sin(ry) * cos(ry) + cos(rx) * sin(rz)) + y * (-sin(rx) * sin(ry) * sin(rz) + cos(rx) * cos(rz)) + vec->z * (-sin(rx) * cos(ry));
	vec->z = x * (-cos(rx) * sin(ry) * cos(rz) + sin(rx) * sin(rz)) + y * (cos(rx) * sin(ry) * sin(rz) + sin(rx) * cos(rz)) + vec->z * (cos(rx) * cos(ry));
}

int    ft_texture(t_ray *ray, double t, t_obj *cur_obj, t_color *col)
{
	float       teta;
	float       tetaA;
	float       tetaB;
	float       zA;
	float       zB;
	float       z;
	t_vec3      pos;

	ft_normalise(&ray->dir);
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = ray->dir.y * t + ray->pos.y - cur_obj->pos.y;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	//  ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	z = pos.y;
	teta = acos((pos.x) / cur_obj->rayon);
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = cur_obj->mat.tex.height;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	ft_normalise(&cur_obj->dir);
	//  ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	zA = pos.y;
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = cur_obj->mat.tex.width;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	//  ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	zB = pos.y;
	tetaA = acos(-1);
	tetaB = acos(1);
	if (teta < tetaA && teta > tetaB && z < zB && z > zA)
	{
		*col = ft_get_tex_color((int)((teta - tetaA) / (tetaB - tetaA) * cur_obj->mat.tex.width1), (int)(cur_obj->mat.tex.height1 - (((z - zA) / (zB - zA)) * cur_obj->mat.tex.height1)), cur_obj);
		return (1);
	}
	return(0);
}

unsigned int  ft_texture_sphere(t_ray *ray, double t, t_obj *cur_obj, t_color *col)
{
	float	s;

	s = (acos((ray->dir.y * t + ray->pos.y - cur_obj->pos.y) / cur_obj->rayon) / M_PI);
	*col = ft_get_tex_color((int)(s * cur_obj->mat.tex.height1),
			(int)((acos((ray->dir.x * t + ray->pos.x - cur_obj->pos.x)
						/ (cur_obj->rayon * sin(M_PI * s))) / (2 * M_PI)) * cur_obj->mat.tex.width1), cur_obj);
	return (1);
}

unsigned int  ft_texture_cone( t_ray *ray, double t, t_obj *cur_obj, t_color *col)
{
	float	teta;
	float	tetaA;
	float	tetaB;
	float	zA;
	float	zB;
	float	z;
	float	rayon;
	t_vec3	pos;

	ft_normalise(&ray->dir);
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = ray->dir.y * t + ray->pos.y - cur_obj->pos.y;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	//  ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	rayon = sqrt(pow(pos.x, 2) + pow(pos.z, 2));
	z = pos.y;
	teta = acos((pos.x) / rayon);
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = cur_obj->mat.tex.height;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	ft_normalise(&cur_obj->dir);
	//ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	zA = pos.y;
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = cur_obj->mat.tex.width;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	//	ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	zB = pos.y;
	tetaA = acos(-1);
	tetaB = acos(1);
	if (teta < tetaA && teta > tetaB && z < zB && z > zA)
	{
		*col = ft_get_tex_color((int)((teta - tetaA) / (tetaB - tetaA) * cur_obj->mat.tex.width1), (int)(cur_obj->mat.tex.height1 - (((z - zA) / (zB - zA)) * cur_obj->mat.tex.height1)), cur_obj);
		return (1);
	}
	return(0);
}

unsigned int ft_texture_plan(t_ray *ray, double t, t_obj *cur_obj, t_color *col)
{
	float	z;
	float	zB;
	float	y;
	float	yB;

	z = 0;
	y = 0;
	if (cur_obj->norm.x == 1 || cur_obj->norm.x == -1)
	{
		z = ray->dir.z * t + ray->pos.z;
		y = ray->dir.y * t + ray->pos.y;
	}
	else if (cur_obj->norm.z == 1 || cur_obj->norm.z == -1)
	{
		z = ray->dir.x * t + ray->pos.x;
		y = ray->dir.y * t + ray->pos.y;
	}
	else if (cur_obj->norm.y == 1 || cur_obj->norm.y == -1)
	{
		z = ray->dir.x * t + ray->pos.x;
		y = ray->dir.z * t + ray->pos.z;
	}
	zB = cur_obj->mat.tex.off_x - cur_obj->mat.tex.width;
	yB = cur_obj->mat.tex.off_y - cur_obj->mat.tex.height;
	if (z < cur_obj->mat.tex.off_x && z > zB && y < cur_obj->mat.tex.off_y && y > yB)
	{
		*col = ft_get_tex_color((int)(((z - zB) / (cur_obj->mat.tex.off_x - zB)) * cur_obj->mat.tex.width1),
				(int)(cur_obj->mat.tex.height1 - (((y - yB) / (cur_obj->mat.tex.off_y - yB)) * cur_obj->mat.tex.height1)), cur_obj);
		return (1);
	}
	return (0);
}

int		ft_select_texture(t_ray *ray, double t, t_obj *cur_obj, t_color *col)
{
	if (cur_obj->get_inters == inters_cyl)
		ft_texture(ray, t, cur_obj, col);
	else if (cur_obj->get_inters == inters_cone)
		ft_texture_cone(ray, t, cur_obj, col);
	else if (cur_obj->get_inters == inters_sphere)
		ft_texture_sphere(ray, t, cur_obj, col);
	else if (cur_obj->get_inters == inters_plan) //&& (cur_obj->norm.y == -1 || cur_obj->norm.y == 1))
		ft_texture_plan(ray, t, cur_obj, col);
	return(1);
}
