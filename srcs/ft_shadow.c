/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:09:10 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/11 14:17:22 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void			ft_free(double **coul, t_env *e)
{
	int i;

	i = 0;
	while (i < e->nb_light)
	{
		free(coul[i]);
		i++;
	}
}

int				ft_behind_obj(int j, int i, double **coul, t_env *e)
{
	double			tmp;

	tmp = ft_dist(j, e);
	if (tmp < ft_dist_light(e, i) && tmp > 0)
		return (0);
	else
	{
		coul[i][0] = coul[i][0] +
			e->light[i].colr * (ft_angle_contact(e, e->ray.obj) +
			ft_fpower(ft_brillance(e, e->ray.obj), 20) *
			e->obj[e->ray.obj].brim);
		coul[i][1] = coul[i][1] +
			e->light[i].colg * (ft_angle_contact(e, e->ray.obj) +
			ft_fpower(ft_brillance(e, e->ray.obj), 20) *
			e->obj[e->ray.obj].brim);
		coul[i][2] = coul[i][2] +
			e->light[i].colb * (ft_angle_contact(e, e->ray.obj) +
			ft_fpower(ft_brillance(e, e->ray.obj), 20) *
			e->obj[e->ray.obj].brim);
		return (1);
	}
}

static void		ft_in_light(double colres[3], t_env *e, int i, double **coul)
{
	int	j;
	int	b;

	b = 1;
	coul[i] = (double*)malloc(sizeof(double) * 3);
	coul[i][0] = 0;
	coul[i][1] = 0;
	coul[i][2] = 0;
	ft_recalc_dir(e, i);
	j = 0;
	while (j < e->nb_obj && b)
	{
		b = ft_behind_obj(j, i, coul, e);
		j++;
	}
	if (b)
	{
		colres[0] = colres[0] + coul[i][0];
		colres[1] = colres[1] + coul[i][1];
		colres[2] = colres[2] + coul[i][2];
	}
}

static void		ft_bri_max(double colres[3])
{
	if (colres[0] >= 1)
		colres[0] = 1;
	if (colres[1] >= 1)
		colres[1] = 1;
	if (colres[2] >= 1)
		colres[2] = 1;
}

unsigned int	ft_ishadow(t_env *e)
{
	double	**coul;
	double	colres[3];
	int		i;

	i = 0;
	coul = (double**)malloc(sizeof(double*) * e->nb_light);
	colres[0] = 0;
	colres[1] = 0;
	colres[2] = 0;
	ft_recalc_ori(e);
	while (i < e->nb_light)
	{
		ft_in_light(colres, e, i, coul);
		i++;
	}
	ft_bri_max(colres);
	ft_free(coul, e);
	free(coul);
	return (65536 * (unsigned int)((e->obj[e->ray.obj].colr * 255) * colres[0])
			+ 256 * (unsigned int)((e->obj[e->ray.obj].colg * 255) * colres[1])
			+ (unsigned int)((e->obj[e->ray.obj].colb * 255) * colres[2]));
}
