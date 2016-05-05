/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_composed_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 13:58:35 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/05 16:03:27 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Géométrie de construction de solides


#include "rtv1.h"

t_obj		*ft_union_obj(t_nod *nod1, t_nod *nod2, t_ray *ray)
{
	double	t1;
	double	t2;
	t_obj	*obj1;
	t_obj	*obj2;

	obj1 = (nod1->op == NULL) ? nod1->obj : nod1->op(nod1->l, nod1->r);
	obj2 = (nod2->op == NULL) ? nod2->obj : nod2->op(nod2->l, nod2->r);
	if (obj1 == NULL)
		t1 = FAR;
	else
		t1 = obj1->get_inters(ray, obj1);
	if (obj2 == NULL)
		t2 = FAR;
	else
		t2 = obj2->get_inters(ray, obj1);
	if (t1 == FAR && t2 == FAR)
		return (NULL);
	return (t1 <= t2 ? obj1 : obj2);
}

t_obj		*ft_inters_obj(t_nod *nod1, t_nod *nod2, t_ray *ray)
{
	double	t1;
	double	t2;
	t_obj	*obj1;
	t_obj	*obj2;

	obj1 = (nod1->op == NULL) ? nod1->obj : nod1->op(nod1->l, nod1->r);
	if (!obj1)
		return (NULL);
	obj2 = (nod2->op == NULL) ? nod2->obj : nod2->op(nod2->l, nod2->r);
	if (!obj1 || !obj2)
		return (NULL);
	t1 = obj1->get_inters(ray, obj1);
	t2 = obj2->get_inters(ray, obj1);
	if (t1 == FAR || t2 == FAR)
		return (NULL);
	return (t1 >= t2 ? obj1 : obj2);
}

t_obj		*ft_sub_obj(t_nod *nod1, t_nod *nod2, t_ray *ray)
{
	double*	t1;
	double*	t2;
	t_obj	*obj1;
	t_obj	*obj2;

	obj1 = (nod1->op == NULL) ? nod1->obj : nod1->op(nod1->l, nod1->r);
	obj2 = (nod2->op == NULL) ? nod2->obj : nod2->op(nod2->l, nod2->r);
	if (obj1 != NULL)
		t1 = obj1->get_inters(ray, obj1);
	else
		return (NULL)
	if (obj2 != NULL)
		t2 = obj2->get_inters(ray, obj1);
	else
		return (obj1);
	if (t1[0] == FAR)
	{
		free(t1);
		free(t2);
		return (NULL);
	}
	if (t1[1] >= t2[1])
	{
		free(t1);
		free(t2);
		return (NULL);
	}
	free(t1);
	free(t2);
	return (obj2);
}
