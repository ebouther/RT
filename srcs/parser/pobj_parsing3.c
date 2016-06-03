/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pobj_parsing3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 11:29:23 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/03 11:30:38 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_read_face(t_obj *pobj, char *line, int size[3])
{
	char	*c;
	t_face	face;

	c = line;
	while (*c != ' ')
		c++;
	if ((face.v1 = ft_atoi(++c) - 1) >= size[0])
		ft_error_exit("Error: invalid .obj file (1to many faces).\n");
	while (*c != '/')
		c++;
	if ((face.vn = ft_atoi(c + 2) - 1) >= size[1])
		ft_error_exit("Error: invalid .obj file (2to many faces).\n");
	while (*c != ' ')
		c++;
	if ((face.v2 = ft_atoi(++c) - 1) >= size[0])
		ft_error_exit("Error: invalid .obj file (3to many faces).\n");
	while (*c != ' ')
		c++;
	if ((face.v3 = ft_atoi(++c) - 1) >= size[0])
		ft_error_exit("Error: invalid .obj file (4to many faces).\n");
	ft_lstadd(&pobj->face, ft_lstnew((void *)&face, sizeof(t_obj)));
}

void		ft_cp_vec3(t_vec3 *dst, t_vec3 *src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

void		ft_tab_vec(t_obj *pobj, int size[3], t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = size[1] - 1;
	tmp = lst;
	if ((pobj->v = (t_vec3*)malloc(sizeof(t_vec3) * size[0])) == NULL)
		ft_error_exit("Error: invalid path for the .obj file\n");
	if ((pobj->vn = (t_vec3*)malloc(sizeof(t_vec3) * size[1])) == NULL)
		ft_error_exit("Error: invalid path for the .obj file\n");
	while (i >= 0)
	{
		ft_cp_vec3(&(pobj->vn)[i], ((t_vec3*)(tmp->content)));
		tmp = tmp->next;
		i--;
	}
	i = size[0] - 1;
	while (i >= 0)
	{
		ft_cp_vec3(&(pobj->v)[i], ((t_vec3*)(tmp->content)));
		tmp = tmp->next;
		i--;
	}
}

void		ft_read_vec(t_list **lst, char *line)
{
	t_vec3	*vec;
	char	*c;

	if ((vec = (t_vec3*)malloc(sizeof(t_vec3))) == NULL)
		ft_error_exit("Error: in malloc vec file\n");
	c = line;
	while (*c != ' ')
	{
		c++;
	}
	vec->x = ft_atod(++c);
	while (*c != ' ')
	{
		c++;
	}
	vec->y = ft_atod(++c);
	while (*c != ' ')
	{
		c++;
	}
	vec->z = ft_atod(++c);
	ft_lstadd(lst, ft_lstnew((void*)vec, sizeof(t_vec3)));
}
