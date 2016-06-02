/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_composed_obj2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/02 11:35:18 by jbelless          #+#    #+#             */
/*   Updated: 2016/06/02 11:48:07 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_nb_nod(t_nod *nod)
{
	return (nod->op == empty ? 1 : ft_nb_nod(nod->l) + ft_nb_nod(nod->r));
}

void	ft_free_tcol(t_obj_col *tcol, double n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free(tcol[i].t);
		i++;
	}
	free(tcol);
}

void	ft_free_tnod(t_nod *tnod)
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

int		ft_opop(double t, t_nod *nod)
{
	if (nod->op == inters)
		return (ft_opop(t, nod->l) && ft_opop(t, nod->r));
	else if (nod->op == sub)
		return (ft_opop(t, nod->l) && !ft_opop(t, nod->r));
	else if (nod->op == uni)
		return (ft_opop(t, nod->l) || ft_opop(t, nod->r));
	else
	{
		if (t >= nod->obj_col->t[0] && t < nod->obj_col->t[1])
			return (1);
		else
			return (0);
	}
}

void	ft_sort_tnod(t_obj_col *tcol, t_nod *tnod, double n)
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
