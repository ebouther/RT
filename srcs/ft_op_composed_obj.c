/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_composed_obj.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 13:58:35 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/26 14:38:29 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_obj_col		*ft_treecpy2(t_obj_col *tcol, t_nod **dest, t_nod *src, t_ray *ray)
{
	t_obj_col *tmp;	

	*dest = (t_nod *)malloc(sizeof(t_nod));	
	tmp = tcol;
	if (src->op == empty)
	{
		(*dest)->obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
		(*dest)->obj_col->t = src->obj->get_inters(ray, src->obj);
		tcol->t = (double*)malloc(sizeof(double) * 2);
		tcol->t[0] = (*dest)->obj_col->t[0];
		tcol->t[1] = (*dest)->obj_col->t[1];
		(*dest)->obj_col->obj = src->obj;
		(*dest)->obj = src->obj;
		(*dest)->op = empty;
		return (tmp++);
	}
	else
	{
		(*dest)->op = src->op;
		tmp = ft_treecpy2(tmp, &(*dest)->l, src->l, ray);
		tmp = ft_treecpy2(tmp, &(*dest)->r, src->r, ray);
	}
	return (tmp);
}


int				ft_opop(double t, t_nod* nod)
{
	if (nod->op == inters)
		return(ft_opop(t, nod->l) && ft_opop(t, nod->r));
	else if (nod->op == sub)
		return(ft_opop(t, nod->l) && !ft_opop(t, nod->r));
	else if (nod->op == uni)
		return(ft_opop(t, nod->l) || ft_opop(t, nod->r));
	else
	{
		if (t >= nod->obj_col->t[0] && t <= nod->obj_col->t[1])
			return (1);
		else
			return (0);
	}
}

void			ft_sort_tnod(t_obj_col *tcol, t_nod *tnod, double n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (tcol[i].t[0] == FAR || !ft_opop(tcol[i].t[0], tnod))
			tcol[i].t[0] = FAR;
		if (tcol[i].t[1] == FAR || !ft_opop(tcol[i].t[1], tnod))
			tcol[i].t[1] = FAR;
		i++;
	}
}

t_obj_col		*ft_min_nod(t_obj_col* tnod, int n)
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
		if (tmp > tnod[i].t[0] || tmp > tnod[i].t[1] )
		{
			tmp = fmin(tnod[i].t[0],tnod[i].t[1]);
			k = i;
		}
	}	
	res = (t_obj_col *)malloc(sizeof(t_obj_col));
	res->obj = tnod[k].obj;
	res->t = (double *)malloc(sizeof(double) * 2);
	res->t[0] = fmin(tnod[k].t[0], tnod[k].t[1]);
	res->t[1] = FAR;
	return (res); 
}

double			ft_nb_nod(t_nod *nod)
{
	return (nod->op == empty ? 1 : ft_nb_nod(nod->l) + ft_nb_nod(nod->r));
}

void			ft_free_tcol(t_obj_col *tcol, double n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(tcol[i].t);
		free(tcol[i].t);
		i++;
	}
	free(tcol);
}

void			ft_free_tnod(t_nod *tnod)
{
	if (tnod->op == empty)
	{
		free(tnod->obj_col->t);
		free(tnod->obj_col);
		free(tnod);
	}
	else
	{
		ft_free_tnod(tnod->l);
		ft_free_tnod(tnod->r);
	}
}

t_obj_col		*ft_get_inters(t_nod *nod, t_ray *ray)
{
	t_obj_col	*res;
	t_nod		*tnod;
	t_obj_col	*tcol;
	double		n;

	n = ft_nb_nod(nod);
	if (nod->op == empty)
	{
		tnod = NULL;
		tcol = NULL;
		res = (t_obj_col*)malloc(sizeof(t_obj_col));
		res->obj = nod->obj;
		res->t = nod->obj->get_inters(ray, nod->obj);
	}
	else
	{
		tcol = (t_obj_col*)malloc(sizeof(t_obj_col) * n);
		ft_treecpy2(tcol, &tnod, nod, ray);
		ft_sort_tnod(tcol, tnod, n);
	}
	res = ft_min_nod(tcol, n);
	if (tnod)
		ft_free_tnod(tnod);
	if (tcol)
		ft_free_tcol(tcol, n);
	return (res);
}
