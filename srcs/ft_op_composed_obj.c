/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_composed_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 13:58:35 by ascholle          #+#    #+#             */
/*   Updated: 2016/06/02 11:58:43 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_treecpy2(t_obj_col **tcol, t_nod **dest, t_nod *src, t_ray *ray)
{
	*dest = (t_nod *)malloc(sizeof(t_nod));
	if (src->op == empty)
	{
		(*dest)->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
		(*dest)->obj_col->t = src->obj->get_inters(ray, src->obj);
		(**tcol).t = (double*)malloc(sizeof(double) * 2);
		(**tcol).t[0] = (*dest)->obj_col->t[0];
		(**tcol).t[1] = (*dest)->obj_col->t[1];
		(**tcol).obj = src->obj;
		(*dest)->obj_col->obj = src->obj;
		(*dest)->obj = src->obj;
		(*dest)->op = empty;
		(*tcol)++;
	}
	else
	{
		(*dest)->op = src->op;
		ft_treecpy2(tcol, &(*dest)->l, src->l, ray);
		ft_treecpy2(tcol, &(*dest)->r, src->r, ray);
	}
}

t_obj_col	*ft_min_nod(t_obj_col *tcol, int n)
{
	int			i;
	int			k;
	double		tmp;
	t_obj_col	*res;

	i = 0;
	tmp = FAR;
	k = 0;
	while (i < n)
	{
		if (tmp > tcol[i].t[0] || tmp > tcol[i].t[1])
		{
			tmp = fmin(tcol[i].t[0], tcol[i].t[1]);
			k = i;
		}
		i++;
	}
	res = (t_obj_col *)malloc(sizeof(t_obj_col));
	res->obj = tcol[k].obj;
	res->t = (double *)malloc(sizeof(double) * 2);
	res->t[0] = fmin(tcol[k].t[0], tcol[k].t[1]);
	res->t[1] = FAR;
	res->obj = tcol[k].obj;
	return (res);
}

t_obj_col	*ft_empty_nod(t_nod *nod, t_ray *ray)
{
	t_obj_col *res;

	res = (t_obj_col*)malloc(sizeof(t_obj_col));
	res->obj = nod->obj;
	res->t = nod->obj->get_inters(ray, nod->obj);
	return (res);
}

t_obj_col	*ft_get_inters(t_nod *nod, t_ray *ray)
{
	t_obj_col	*res;
	t_nod		*tnod;
	t_obj_col	*tcol;
	t_obj_col	*sv;
	double		n;

	tnod = NULL;
	tcol = NULL;
	if (nod->op == empty)
		res = ft_empty_nod(nod, ray);
	else
	{
		n = ft_nb_nod(nod);
		tcol = (t_obj_col*)malloc(sizeof(t_obj_col) * n);
		sv = tcol;
		ft_treecpy2(&tcol, &tnod, nod, ray);
		tcol = sv;
		ft_sort_tnod(tcol, tnod, n);
		res = ft_min_nod(tcol, n);
	}
	if (tnod)
		ft_free_tnod(tnod);
	if (tcol)
		ft_free_tcol(tcol, n);
	return (res);
}
