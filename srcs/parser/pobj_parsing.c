/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pobj_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 10:28:22 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/31 12:06:02 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

static void	ft_read_face(t_obj *pobj, char *line, int size[2])
{
	char 	*c;
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

static void	ft_tab_vect(t_obj *pobj, int size[2], t_list *lst)
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
		(pobj->vn)[i].x =((t_vec3*)(tmp->content))->x;
		(pobj->vn)[i].y =((t_vec3*)(tmp->content))->y;
		(pobj->vn)[i].z =((t_vec3*)(tmp->content))->z;
		tmp = tmp->next;
		i--;
	}
	i = size[0] - 1;
	while (i >= 0)
	{
		(pobj->v)[i].x =((t_vec3*)(tmp->content))->x;
		(pobj->v)[i].y =((t_vec3*)(tmp->content))->y;
		(pobj->v)[i].z =((t_vec3*)(tmp->content))->z;
		tmp = tmp->next;
		i--;
	}
}

static void	ft_read_vec(t_list **lst, char *line)
{
	t_vec3	*vec;
	char	*c;

	if ((vec = (t_vec3*)malloc(sizeof(t_vec3))) == NULL)
		ft_error_exit("Error: in malloc vec file\n");
	c = line;
	while(*c != ' ')
	{
		c++;
	}
	vec->x = ft_atod(++c);
	while(*c != ' ')
	{
		c++;
	}
	vec->y = ft_atod(++c);
	while(*c != ' ')
	{
		c++;
	}
	vec->z = ft_atod(++c);
	ft_lstadd(lst, ft_lstnew((void*)vec, sizeof(t_vec3)));
}

static void	ft_read_pobj(char *path, t_obj *pobj)
{
	int		fd;
	char	*line;
	int		ret;
	int		size[2];
	t_list	*lst;
	int i = 0;

	lst = NULL;
	if ((fd = open(path, O_RDONLY)) == -1)
		ft_error_exit("Error: invalid path for the .obj file\n");
	size[0] = 0; 
	size[1] = 0; 
	pobj->v = NULL;
	pobj->face = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (*line == 'v')
		{
			if (*(line + 1) == ' ')
				size[0] ++;
			else if (*(line + 1 ) == 'n')
				size[1] ++;
			ft_read_vec(&lst, line);
		}
		else if (*line == 'f')
		{
			if (pobj->v == NULL)
				ft_tab_vect(pobj, size, lst);
			ft_read_face(pobj, line, size);
			i++;
		}
	}
	if (ret == -1)
		ft_error_exit("Error: no read possible for the .obj file\n");
	
	printf("il y a %d sommet, %d vecteurs normaux et %d faces\n",size[0], size[1],i);
}

int			ft_set_pobj(char *pobj, t_env *e, t_nod *prnt)
{
	char	*position;
	char	*radius;
	char	*path;
	char	*mat;
	t_nod	nod;

	nod.obj = (t_obj*)malloc(sizeof(t_obj));
	nod.obj->mat.brim = 0.1;
	if ((position = ft_get_inner(pobj, "position", NULL, NULL)) == NULL)
		ft_error_exit("Error: pobj require a position subobject.\n");
	if ((path = ft_get_inner(pobj, "path", NULL, NULL)) == NULL)
		ft_error_exit("error: pobj require a path to the .obj file.\n");
	if ((radius = ft_get_inner(pobj, "radius", NULL, NULL)) == NULL)
		ft_error_exit("Error: pobj require a radius subobject.\n");
	if ((mat = ft_get_inner(pobj, "mat", NULL, NULL)) == NULL)
		ft_error_exit("Error: pobj require a material subobject.\n");
	ft_set_vec3(position, &nod.obj->pos);
	nod.obj->rayon = ft_atod(radius);
	ft_set_mat(mat, nod.obj);
	ft_read_pobj(path, nod.obj);
	nod.obj->get_normal = &normal_pobj;
	nod.obj->get_inters = &inters_pobj;
	nod.r = NULL;
	nod.l = NULL;
	nod.op = empty;
	nod.obj_col = (t_obj_col *)malloc(sizeof(t_obj_col));
	if (e)
		ft_lstadd(&e->obj, ft_lstnew((void *)&nod, sizeof(t_nod)));
	else
		ft_memcpy(prnt, &nod, sizeof(t_nod));
	ft_strdel(&position);
	ft_strdel(&radius);
	ft_strdel(&path);
	ft_strdel(&mat);
	return (0);
}

int			ft_get_pobjs(char *objects, size_t len, t_env *e)
{
	char	*pobj;
	int		pos;

	pos = 0;
	while ((pobj = ft_get_inner(objects, "pobj", &pos, NULL)) != NULL)
	{
		ft_set_pobj(pobj, e, NULL);
		ft_strdel(&pobj);
		if ((int)len - pos < 0)
			break ;
		objects += pos;
	}
	return (0);
}
