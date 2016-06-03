/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 14:52:39 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/03 14:52:51 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_stock_size_tex(t_obj *cur_obj)
{
	t_norm_stock_size_tex	norm;

	norm.i = 0;
	norm.buf = NULL;
	if ((norm.fd = open(cur_obj->mat.tex.tex, O_RDONLY)) == -1)
		ft_error_exit("error: bad texture file path.\n");
	while (norm.i++ != 4)
		norm.res = get_next_line(norm.fd, &norm.buf);
	norm.split = ft_strsplit(norm.buf, ' ');
	norm.width = ft_strdup(norm.split[0]);
	norm.height = ft_strdup(norm.split[1]);
	norm.i = 0;
	while (norm.split[norm.i])
		ft_strdel(norm.split + norm.i++);
	free(norm.split);
	cur_obj->mat.tex.width1 = atoi(norm.width + 1);
	cur_obj->mat.tex.height1 = atoi(norm.height);
	ft_strdel(&norm.width);
	ft_strdel(&norm.height);
	close(norm.fd);
}

void	ft_init_tex_node(t_nod *node, t_env *e)
{
	if (node->op == empty)
	{
		if (node->obj->mat.tex.tex != NULL)
		{
			ft_stock_size_tex(node->obj);
			node->obj->mat.tex.img =
				mlx_xpm_file_to_image(e->mlx, node->obj->mat.tex.tex,
						&node->obj->mat.tex.width1,
						&node->obj->mat.tex.height1);
			node->obj->mat.tex.buf =
				mlx_get_data_addr(node->obj->mat.tex.img,
						&node->obj->mat.tex.bpp,
						&node->obj->mat.tex.ls,
						&node->obj->mat.tex.endian);
		}
	}
	else
	{
		ft_init_tex_node(node->l, e);
		ft_init_tex_node(node->r, e);
	}
}

void	init_tex(t_env *e)
{
	t_list	*lst;

	lst = e->obj;
	while (lst)
	{
		ft_init_tex_node(((t_nod*)(lst->content)), e);
		lst = lst->next;
	}
}
