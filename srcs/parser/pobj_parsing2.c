/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pobj_parsing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 11:31:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/03 11:32:29 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_read_pobj2(char *line, t_list **lst, int size[3], t_obj *pobj)
{
	if (*line == 'v')
	{
		if (*(line + 1) == ' ')
			size[0]++;
		else if (*(line + 1) == 'n')
			size[1]++;
		ft_read_vec(lst, line);
	}
	else if (*line == 'f')
	{
		if (pobj->v == NULL)
			ft_tab_vec(pobj, size, *lst);
		ft_read_face(pobj, line, size);
	}
}

void		ft_read_pobj(char *path, t_obj *pobj)
{
	int		fd;
	char	*line;
	int		size[3];
	t_list	*lst;

	lst = NULL;
	if ((fd = open(path, O_RDONLY)) == -1)
		ft_error_exit("Error: invalid path for the .obj file\n");
	size[0] = 0;
	size[1] = 0;
	pobj->v = NULL;
	pobj->face = NULL;
	while ((size[2] = get_next_line(fd, &line)) > 0)
	{
		ft_read_pobj2(line, &lst, size, pobj);
	}
	if (size[2] == -1)
		ft_error_exit("Error: no read possible for the .obj file\n");
}
