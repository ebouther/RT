/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/13 11:58:50 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void		ft_in_light(t_work *work, t_env *e, t_color_res *col_res)
{
	t_list	*lst;
	double	tmp;
	t_color_res	col_add;
	double	angle_contact;
	t_color	filtre;

	col_add = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	ft_recalc_dir(work->light, work->ray, work->normal);
	lst = e->obj;
	filtre = (t_color){work->light->col.r, work->light->col.g, work->light->col.b};
	while (lst)
	{
		tmp = ((t_obj *)(lst->content))->get_inters(work->ray, (t_obj *)(lst->content));
		if (((t_obj *)(lst->content))->mat.refr > 0 && tmp > 0 && tmp < ft_dist_light(&work->ray->pos, &work->light->pos) )
		{
			filtre.r *= ((t_obj *)(lst->content))->mat.col.r * ((t_obj *)(lst->content))->mat.refr;
			filtre.g *= ((t_obj *)(lst->content))->mat.col.g * ((t_obj *)(lst->content))->mat.refr;
			filtre.b *= ((t_obj *)(lst->content))->mat.col.b * ((t_obj *)(lst->content))->mat.refr;
		}
		else if (!(tmp > ft_dist_light(&work->ray->pos, &work->light->pos) || tmp < 0))
			break;
		lst = lst->next;
	}
	if (!lst)
	{
		angle_contact = ft_angle_contact(work->ray, work->normal);
		col_add.diffuse.r += filtre.r * angle_contact * work->light->k;
		col_add.specular.r += filtre.r *
			ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) *
			work->obj->mat.brim;
		col_add.diffuse.g += filtre.g * angle_contact * work->light->k;
		col_add.specular.g += filtre.g *
			ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) *
			work->obj->mat.brim;
		col_add.diffuse.b += filtre.b * angle_contact * work->light->k;
		col_add.specular.b += filtre.b *
			ft_fpower(ft_brillance(&e->cam.dir, work->ray, work->normal), 20) *
			work->obj->mat.brim;
		col_res->diffuse.r += col_add.diffuse.r;
		col_res->specular.r += col_add.specular.r;
		col_res->diffuse.g += col_add.diffuse.g;
		col_res->specular.g += col_add.specular.g;
		col_res->diffuse.b += col_add.diffuse.b;
		col_res->specular.b += col_add.specular.b;
	}
}

double	ft_color_clip(double color)
{
	return ((color < 1) ? color : 1);
}

static void		ft_bri_max(t_color_res *colres)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((((t_color *)colres) + i)->r > 1)
			(((t_color *)colres) + i)->r = 1;
		if (((t_color *)colres + i)->g > 1)
			((t_color *)colres + i)->g = 1;
		if (((t_color *)colres + i)->b > 1)
			((t_color *)colres + i)->b = 1;
		i++;
	}
}

void	ft_color_mode(t_color *c, t_env *e)
{
	t_color	in;

	in.r = c->r;
	in.g = c->g;
	in.b = c->b;
	if (e->color_m == 1)
	{
		c->r = ft_color_clip(in.r * 0.393 + in.g * 0.769 + in.b * 0.189);
		c->g = ft_color_clip(in.r * 0.349 + in.g * 0.683 + in.b * 0.168);
		c->b = ft_color_clip(in.r * 0.272 + in.g * 0.534 + in.b * 0.131);
	}
	else if (e->color_m == 2)
	{
		c->r = ft_color_clip((in.r + in.g + in.b) / 3.0);
		c->g = c->r;
		c->b = c->r;
	}
}

t_color     ft_get_tex_color(int x, int y, t_obj *cur_obj)
{
	unsigned char   *c;
	t_color         ret;
	c = (unsigned char*)cur_obj->mat.tex.buf + (x) * (cur_obj->mat.tex.bpp / 8) + ((cur_obj->mat.tex.height1 - y) * cur_obj->mat.tex.ls);
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

int    ft_texture(t_ray *ray, double t, t_obj *cur_obj, t_env *e)
{
	float       teta;
	float       tetaA;
	float       tetaB;
	float       zA;
	float       zB;
	float       z;
	t_color     *col;
	t_vec3      pos;
	//	ft_putendl("ok");
	
	ft_normalise(&ray->dir);
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = ray->dir.y * t + ray->pos.y - cur_obj->pos.y;
	pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
//	ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
	ft_rot_axeZ(asin(cur_obj->dir.x), &pos);
	ft_rot_axeX(asin(cur_obj->dir.z), &pos);
	z = pos.y;
	teta = acos((pos.x) / cur_obj->rayon);
	pos.x = ray->dir.x * t + ray->pos.x - cur_obj->pos.x;
	pos.y = cur_obj->mat.tex.height;
    pos.z = ray->dir.z * t + ray->pos.z - cur_obj->pos.z;
	ft_normalise(&cur_obj->dir);
//	ft_rot2(asin(cur_obj->dir.z), asin(cur_obj->dir.x), &pos);
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
	(void)e;
	if (teta < tetaA && teta > tetaB && z < zB && z > zA)
	{
		if ((col = malloc(sizeof(t_color))) == NULL)
			exit(-1);
		//		printf("VALUE : '%f'\n", t);
		*col = ft_get_tex_color((int)((teta - tetaA) / (tetaB - tetaA) * cur_obj->mat.tex.width1), (int)(((z - zA) / (zB - zA)) * cur_obj->mat.tex.height1), cur_obj);
		cur_obj->mat.texcol.r = col->r;
		cur_obj->mat.texcol.g = col->g;
		cur_obj->mat.texcol.b = col->b;
		return (1);
	}
	return(0);
}

unsigned int  ft_texture_sphere(t_ray *ray, double t, t_obj *cur_obj)
{
	float   s;
	t_color     *col;

	s = (acos((ray->dir.y * t + ray->pos.y - cur_obj->pos.y) / cur_obj->rayon) / M_PI);
	if ((col = malloc(sizeof(t_color))) == NULL)
		exit(-1);
	*col = ft_get_tex_color((int)(s * cur_obj->mat.tex.height1), (int)((acos((ray->dir.x * t + ray->pos.x - cur_obj->pos.x) / (cur_obj->rayon * sin(M_PI * s))) / (2 * M_PI)) * cur_obj->mat.tex.width1), cur_obj);
	cur_obj->mat.texcol.r = col->r;
	cur_obj->mat.texcol.g = col->g;
	cur_obj->mat.texcol.b = col->b;
	return (1);
}

unsigned int  ft_texture_cone( t_ray *ray, double t, t_obj *cur_obj)
{
	float     teta;
	float     tetaA;
	float     tetaB;
	float     zA;
	float     zB;
	float     z;
	float     rayon;
	t_color       *col;

	rayon = sqrt(pow(ray->dir.x * t + ray->pos.x - cur_obj->pos.x, 2) + pow(ray->dir.z * t + ray->pos.z - cur_obj->pos.z, 2));
	teta = acos((ray->dir.x * t + ray->pos.x - cur_obj->pos.x) / rayon);
	z = ray->dir.y * t + ray->pos.y;
	zA = cur_obj->mat.tex.height;
	zB = cur_obj->mat.tex.width;
	tetaA = acos(-1);
	tetaB = acos(1);
	(void)cur_obj;
	if (teta < tetaA && teta > tetaB && z < zB && z > zA)
	{
		if ((col = malloc(sizeof(t_color))) == NULL)
			exit(-1);
		//		printf("VALUE : '%f'\n", t);
		*col = ft_get_tex_color((int)((acos((ray->dir.x * t + ray->pos.x - cur_obj->pos.x) / rayon) - tetaA) / (tetaB - tetaA) * cur_obj->mat.tex.width1), (int)(((z - zA) / (zB - zA)) * cur_obj->mat.tex.height1), cur_obj);
		cur_obj->mat.texcol.r = col->r;
		cur_obj->mat.texcol.g = col->g;
		cur_obj->mat.texcol.b = col->b;
		return (1);
	}
	return(0);
}

unsigned int ft_texture_plan(t_ray *ray, double t, t_obj *cur_obj)
{
	float	z;
	float	zB;
	float	y;
	float	yB;
	t_color       *col;

	z = 0;
	y = 0;	
	if(cur_obj->norm.x == 1 || cur_obj->norm.x == -1)
	{	
		z = ray->dir.z * t + ray->pos.z;
		y = ray->dir.y * t + ray->pos.y;
	}
	else if(cur_obj->norm.z == 1 || cur_obj->norm.z == -1)
	{
		z = ray->dir.x * t + ray->pos.x;
		y = ray->dir.y * t + ray->pos.y;
	}
	else if(cur_obj->norm.y == 1 || cur_obj->norm.y == -1)
	{
		z = ray->dir.x * t + ray->pos.x;
		y = ray->dir.z * t + ray->pos.z;
	}
	zB = cur_obj->mat.tex.off_x - cur_obj->mat.tex.width;
	yB = cur_obj->mat.tex.off_y - cur_obj->mat.tex.height;
	if(z < cur_obj->mat.tex.off_x && z > zB && y < cur_obj->mat.tex.off_y && y > yB)
	{
		if ((col = malloc(sizeof(t_color))) == NULL)
			exit(-1);
		*col = ft_get_tex_color((int)(((z - zB) / (cur_obj->mat.tex.off_x - zB)) * cur_obj->mat.tex.width1), (int)(((y - yB) / (cur_obj->mat.tex.off_y - yB)) * cur_obj->mat.tex.height1), cur_obj);
		/*if(cur_obj->norm.z == 1 || cur_obj->norm.z == -1)
		{
			printf("x: %d, y: %d , %d\n",(int)(((z - zB) / (cur_obj->mat.tex.off_x - zB)) * cur_obj->mat.tex.width1), (int)(((y - yB) / (cur_obj->mat.tex.off_y - yB)) * cur_obj->mat.tex.height1), ((int)(((z - zB) / (cur_obj->mat.tex.off_x - zB)) * cur_obj->mat.tex.width1)) * (cur_obj->mat.tex.bpp / 8) + ((cur_obj->mat.tex.height1 - (int)(((y - yB) / (cur_obj->mat.tex.off_y - yB)) * cur_obj->mat.tex.height1)) * cur_obj->mat.tex.ls));
		}*/

		cur_obj->mat.texcol.r = col->r;
		cur_obj->mat.texcol.g = col->g;
		cur_obj->mat.texcol.b = col->b;

	}
	/*if(z == 0 || y == 300)
	{
		cur_obj->mat.texcol.r = 0;
		cur_obj->mat.texcol.g = 1;
		cur_obj->mat.texcol.b = 0;
	}*/
	
	return(1);
}

static void	ft_checkerboard(t_ray *ray, t_obj *cur_obj, double t, t_color col)
{
	t_vec3	pos;

	pos = (t_vec3){ray->dir.x * t + ray->pos.x, ray->dir.y * t + ray->pos.y, ray->dir.z * t + ray->pos.z};
	if ((int)pos.y <= 0)
		pos.y--;
	if ((int)pos.x <= 0)
		pos.x--;
	if (((int)pos.x + (int)pos.y) % 2 == 0)
		cur_obj->mat.texcol = col;
}

t_color		*ft_ishadow(t_env *e, t_ray *ray, double t, t_obj *cur_obj)
{
	t_color_res	col_res;
	t_list		*lst;
	t_color		*final_col;
	t_work		work;
	double		refl;
	t_ray		*ray_refr;
	t_ray		*ray_refl;
	t_color		*col;

	if (kk)
	{
		printf("\nray iter = %d\n",ray->iter);
		printf("ray_pos = %f, %f, %f\n",ray->pos.x, ray->pos.y, ray->pos.z);
		printf("ray_dir = %f, %f, %f\n",ray->dir.x, ray->dir.y, ray->dir.z);
		printf("cur obj : opac %f, refl %f\n",cur_obj->mat.opac, cur_obj->mat.refl);

	}
	work.obj = cur_obj;
	col_res = (t_color_res){{0, 0, 0}, {0, 0, 0}, NULL, NULL};
	if ((final_col = (t_color*)malloc(sizeof(t_color))) == NULL)
		exit(-1);
	ft_bzero(final_col, sizeof(t_color));
	cur_obj->mat.texcol = cur_obj->mat.col;
	if (cur_obj->mat.grid == TRUE)
		ft_checkerboard(ray, cur_obj, t, (t_color){1, 1, 0});
	if (cur_obj->mat.tex.tex != NULL)
	{
		if (cur_obj->get_inters == inters_cyl)
			if (ft_texture(ray, t, cur_obj, e) == 1)
				col = &cur_obj->mat.texcol;
		if (cur_obj->get_inters == inters_cone)
			if (ft_texture_cone(ray, t, cur_obj) == 1)
				col = &cur_obj->mat.texcol;
		if (cur_obj->get_inters == inters_sphere)
			if (ft_texture_sphere(ray, t, cur_obj) == 1)
				col = &cur_obj->mat.texcol;
		if (cur_obj->get_inters == inters_plan && cur_obj->norm.x == 1)
			if (ft_texture_plan(ray, t, cur_obj) == 1)
				col = &cur_obj->mat.texcol;
		if (cur_obj->get_inters == inters_plan && cur_obj->norm.z == -1)
			if (ft_texture_plan(ray, t, cur_obj) == 1)
				col = &cur_obj->mat.texcol;
		if (cur_obj->get_inters == inters_plan && (cur_obj->norm.y == -1 || cur_obj->norm.y == 1))
			if (ft_texture_plan(ray, t, cur_obj) == 1)
				col = &cur_obj->mat.texcol;
	}
	if (ray->iter >= NB_ITER)
		return ((t_color *)ft_memset(final_col, 0, sizeof(t_color)));

	work.ray = ft_recalc_ori(ray, t);
	if (kk)
		printf("new ori{%d] = %f, %f, %f \n",ray->iter, work.ray->pos.x, work.ray->pos.y, work.ray->pos.z);
	work.normal = cur_obj->get_normal(work.ray, cur_obj);
	if (kk)
		printf("normal[%d] = %f ,%f ,%f\n", ray->iter, work.normal->x, work.normal->y,work.normal->z);
	lst = e->light;
	if (cur_obj->mat.refr > 0)
	{
		ray_refr = ft_refr(ray, &work, &refl);
		col_res.refr = ft_contact(ray_refr, e);
		if (kk)
			printf("col_refr[%d] = %f, %f, %f\n",ray->iter, col_res.refr->r, col_res.refr->g, col_res.refr->b);
	}
	else
		refl = 0;
	if (cur_obj->mat.refl + refl > 0)
	{
		ray_refl = ft_refl(ray, &work);
		col_res.refl = ft_contact(ray_refl, e);
	}
	while (lst)
	{
		work.light = ((t_light *)(lst->content));
		ft_in_light(&work, e, &col_res);
		lst = lst->next;
	}
	if (kk)
		printf("col_diffu[%d] = %f, %f %f\n",ray->iter, col_res.diffuse.r,col_res.diffuse.g,col_res.diffuse.b);
	ft_bri_max(&col_res);
	/*if((cur_obj->mat.texcol.r != cur_obj->mat.col.r || cur_obj->mat.texcol.g != cur_obj->mat.col.g || cur_obj->mat.texcol.b != cur_obj->mat.col.b) && flag == 1)
	  {
	  cur_obj->mat.col.r = cur_obj->mat.texcol.r;
	  cur_obj->mat.col.b = cur_obj->mat.texcol.b;
	  cur_obj->mat.col.g = cur_obj->mat.texcol.g;
	  }*/
	final_col->r = ft_color_clip(e->amb * cur_obj->mat.texcol.r
			+ cur_obj->mat.texcol.r * col_res.diffuse.r * cur_obj->mat.opac + col_res.specular.r + cur_obj->mat.refr * (col_res.refr ? col_res.refr->r : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->r : 0));
	final_col->g = ft_color_clip(e->amb * cur_obj->mat.texcol.g
			+ cur_obj->mat.texcol.g * col_res.diffuse.g * cur_obj->mat.opac + col_res.specular.g + cur_obj->mat.refr * (col_res.refr ? col_res.refr->g : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->g : 0));
	final_col->b = ft_color_clip(e->amb * cur_obj->mat.texcol.b
			+ cur_obj->mat.texcol.b * col_res.diffuse.b * cur_obj->mat.opac + col_res.specular.b + cur_obj->mat.refr * (col_res.refr ? col_res.refr->b : 0) + (cur_obj->mat.refl + refl) * (col_res.refl ? col_res.refl->b : 0));
	ft_color_mode(final_col, e);
	free(work.normal);
	free(work.ray);
	if (kk)
		printf("final[%d] r = %f, g = %f, b= %f\n",ray->iter, final_col->r, final_col->g, final_col->b);
	return (final_col);
}
