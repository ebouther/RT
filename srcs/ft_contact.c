/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contact.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:08:46 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/06 11:11:19 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_get_touched_obj(t_obj_col *tmp, t_obj **cur_obj, t_obj **obj_pix,
		double *t)
{
	if (tmp->t[0] < *t && tmp->t[0] > 0)
	{
		*t = tmp->t[0];
		if (obj_pix)
			*obj_pix = tmp->obj;
		*cur_obj = tmp->obj;
	}
	else if (tmp->t[1] < *t && tmp->t[1] > 0)
	{
		*t = tmp->t[1];
		if (obj_pix)
			*obj_pix = tmp->obj;
		*cur_obj = tmp->obj;
	}
	else
	{
		free(tmp->t);
		free(tmp);
	}
}

t_color		*ft_contact(t_ray *ray, t_env *e, t_obj **obj_pix)
{
	t_obj		*cur_obj;
	t_obj_col	*tmp;
	double		t;
	t_list		*lst;

	if (ray == NULL)
		return (NULL);
	t = FAR;
	lst = e->obj;
	while (lst)
	{
		tmp = ft_get_inters(lst->content, ray);
		ft_get_touched_obj(tmp, &cur_obj, obj_pix, &t);
		lst = lst->next;
	}
	if (t < FAR)
		return (ft_ishadow(e, ray, t, cur_obj));
	return (NULL);
}
