/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_composed_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 13:58:35 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/09 16:59:08 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Géométrie de construction de solides


#include "rtv1.h"

t_obj_col		*ft_union_obj(t_nod *nod1, t_nod *nod2, t_ray *ray)
{
	t_obj_col	*res;

	if (!nod1->op)
	{
		nod1->obj_col->t = nod1->obj->get_inters(ray, nod1->obj);
		nod1->obj_col->obj = nod1->obj;
		nod1->obj_col->neg = 1;
	}
	else
		nod1->obj_col = nod1->op(nod1->l, nod1->r, ray);
	if (!nod2->op)
	{
		nod2->obj_col->t = nod2->obj->get_inters(ray, nod2->obj);
		nod2->obj_col->obj = nod2->obj;
		nod2->obj_col->neg = 1;
	}
	else
		nod2->obj_col = nod2->op(nod2->l, nod2->r, ray);
	if (nod1->obj_col->t[0] < nod2->obj_col->t[0])
		res = nod1->obj_col;
	else
		res = nod2->obj_col;
	return (res);
}

t_obj_col		*ft_inters_obj(t_nod *nod1, t_nod *nod2, t_ray *ray)
{
	t_obj_col	*res;

	if (!nod1->op)
	{
		nod1->obj_col->t = nod1->obj->get_inters(ray, nod1->obj);
		nod1->obj_col->obj = nod1->obj;
		nod1->obj_col->neg = 1;
	}
	else
		nod1->obj_col = nod1->op(nod1->l, nod1->r, ray);
	if (!nod2->op)
	{
		nod2->obj_col->t = nod2->obj->get_inters(ray, nod2->obj);
		nod2->obj_col->obj = nod2->obj;
		nod2->obj_col->neg = 1;
	}
	else
		nod2->obj_col = nod2->op(nod2->l, nod2->r, ray);
	if (nod1->obj_col->t[0] == FAR || nod2->obj_col->t[0] == FAR)
		res = nod2->obj_col;
	else
		res = (nod1->obj_col->t[0] > nod2->obj_col->t[0]) ? nod1->obj_col
			: nod2->obj_col;
	return (res);
}

t_obj_col		*ft_sub_obj(t_nod *nod1, t_nod *nod2, t_ray *ray)
{
	t_obj_col	*res;

	if (!nod1->op)
	{
		nod1->obj_col->t = nod1->obj->get_inters(ray, nod1->obj);
		nod1->obj_col->obj = nod1->obj;
		nod1->obj_col->neg = 1;
	}
	else
		nod1->obj_col = nod1->op(nod1->l, nod1->r, ray);
	if (!nod2->op)
	{
		nod2->obj_col->t = nod2->obj->get_inters(ray, nod2->obj);
		nod2->obj_col->obj = nod2->obj;
		nod2->obj_col->neg = 1;
	}
	else
		nod2->obj_col = nod2->op(nod2->l, nod2->r, ray);
	if (nod1->obj_col->t[0] < nod2->obj_col->t[0])
		res = nod1->obj_col;
	else
	{
		nod2->obj_col->neg = -1;
		res = nod2->obj_col;
	}
	return (res);
}

t_obj_col		*ft_get_inters(t_nod *nod, t_ray *ray)
{
	t_obj_col	*res;

	if (!nod->op)
	{
		res = nod->obj_col;
		res->obj = nod->obj;
		res->t = nod->obj->get_inters(ray, nod->obj);
	}
	else
		res = nod->op(nod->l, nod->r, ray);
	return (res);
}
