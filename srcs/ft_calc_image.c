/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 15:01:22 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/06 11:09:08 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_split_cam(t_vec3 *dist, t_env *e)
{
	dist->x = ((t_env *)e)->cam.right.x * 0.6;
	dist->y = ((t_env *)e)->cam.right.y * 0.6;
	dist->z = ((t_env *)e)->cam.right.z * 0.6;
	((t_env *)e)->cam.pos.x -= dist->x;
	((t_env *)e)->cam.pos.y -= dist->y;
	((t_env *)e)->cam.pos.z -= dist->z;
}

void		ft_find_color(t_env *e, int coor[2], t_color *tmp_col)
{
	((t_env *)e)->pix[coor[0] + coor[1] * SIZE_W].col->r += tmp_col->r;
	((t_env *)e)->pix[coor[0] + coor[1] * SIZE_W].col->g += tmp_col->g;
	((t_env *)e)->pix[coor[0] + coor[1] * SIZE_W].col->b += tmp_col->b;
	free(tmp_col);
}

static void	ft_loop_thread(t_env *e)
{
	int				coor[2];
	int				start;
	int				end;
	t_ray			*ray;
	t_color			*tmp_col;

	start = floor((SIZE_W / THREAD_NUM * ((t_env *)e)->start));
	end = ceil((SIZE_W / THREAD_NUM) * (((t_env *)e)->start + 1));
	coor[0] = start;
	while (coor[0] < end)
	{
		coor[1] = 0;
		while (coor[1] < SIZE_H)
		{
			ray = ft_calc_ray(coor[0], coor[1], ((t_env *)e));
			tmp_col = ft_contact(ray, e, &((t_env *)e)->pix[coor[0] +
					coor[1] * SIZE_W].obj);
			if (tmp_col)
				ft_find_color(e, coor, tmp_col);
			free(ray);
			coor[1]++;
		}
		coor[0]++;
	}
}

void		*ft_fill_img(void *e)
{
	t_vec3			dist;
	int				k;

	k = 0;
	ft_pixmalloc(((t_env *)e)->pix);
	if (((t_env *)e)->color_m >= 3)
		ft_split_cam(&dist, e);
	while ((++k <= 2 && ((t_env *)e)->color_m >= 3) || k == 1)
	{
		ft_loop_thread((t_env *)e);
		((t_env *)e)->cam.pos.x += 2 * dist.x;
		((t_env *)e)->cam.pos.y += 2 * dist.y;
		((t_env *)e)->cam.pos.z += 2 * dist.z;
		((t_env *)e)->color_m++;
	}
	pthread_exit(NULL);
}
