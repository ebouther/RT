/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_composed_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 13:58:35 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/25 18:16:21 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//Géométrie de construction de solides


#include "rtv1.h"
#include <stdio.h>

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
		nod1->obj_col = nod1->op(nod1->r, nod1->l, ray);
	if (!nod2->op)
	{
		nod2->obj_col->t = nod2->obj->get_inters(ray, nod2->obj);
		nod2->obj_col->obj = nod2->obj;
		nod2->obj_col->neg = 1;
	}
	else
		nod2->obj_col = nod2->op(nod2->r, nod2->l, ray);
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
		nod1->obj_col = nod1->op(nod1->r, nod1->l, ray);
	if (!nod2->op)
	{
		nod2->obj_col->t = nod2->obj->get_inters(ray, nod2->obj);
		nod2->obj_col->obj = nod2->obj;
		nod2->obj_col->neg = 1;
	}
	else
		nod2->obj_col = nod2->op(nod2->r, nod2->l, ray);
	if (nod1->obj_col->t[0] < nod2->obj_col->t[0] && nod2->obj_col->t[1] != -FAR ) 
	{
		if (kk)
		{
			printf ("t1[0] = %f,t1[1] = %f ___________1___________\n",nod1->obj_col->t[0], nod1->obj_col->t[1] );
			printf ("t2[0] = %f,t2[1] = %f ___________1___________\n",nod2->obj_col->t[0], nod2->obj_col->t[1] );
		}
		res = nod2->obj_col;
		if (nod1->obj_col->t[1] < nod2->obj_col->t[0]) 
		{
			res->t[0] = FAR;
			res->t[1] = FAR;
			if (kk)
				printf("lolo\n");
		}
	}
	else if (nod2->obj_col->t[0] < nod1->obj_col->t[0] || nod2->obj_col->t[1] != -FAR)
	{
		if (kk)
		{
			printf ("t1[0] = %f,t1[1] = %f ___________2___________\n",nod1->obj_col->t[0], nod1->obj_col->t[1] );
			printf ("t2[0] = %f,t2[1] = %f ___________2___________\n",nod2->obj_col->t[0], nod2->obj_col->t[1] );
		}
		res = nod1->obj_col;
		if (nod2->obj_col->t[1] < nod1->obj_col->t[0])
		{
			res->t[0] = FAR;
			res->t[1] = FAR;
			if (kk)
				printf("lalal\n");
		}
	}
	else
	{
		if (kk)
		{
			printf ("t1[0] = %f,t1[1] = %f ___________3___________\n",nod1->obj_col->t[0], nod1->obj_col->t[1] );
			printf ("t2[0] = %f,t2[1] = %f ___________3___________\n",nod2->obj_col->t[0], nod2->obj_col->t[1] );
		}
		res = nod1->obj_col;
		res->t[0] = FAR;
		res->t[1] = FAR;
	}
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
	if (nod1->obj_col->t[0] < nod2->obj_col->t[0] || nod2->obj_col->t[1] <= nod1->obj_col->t[0])
		res = nod1->obj_col;
	else
	{
		if (nod2->obj_col->t[1] < nod1->obj_col->t[1])
		{
			res = nod2->obj_col;
			res->t[0] = res->t[1];
		}
		else
		{
			res = nod1->obj_col;
			res->t[0] = FAR;
		}
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
		res = nod->op(nod->r, nod->l, ray);
	return (res);
}
