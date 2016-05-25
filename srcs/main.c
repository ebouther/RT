/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:52:18 by jbelless          #+#    #+#             */
/*   Updated: 2016/05/19 13:26:41 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_init_env(t_env *e)
{
	e->obj = NULL;
	e->c_obj = NULL;
	e->light = NULL;
	e->mlx = NULL;
	e->win = NULL;
	e->img = NULL;
	e->data = NULL;
}

void	ft_stock_scene(t_env *e, char *av)
{
	int		fd;
	char	*line;
	char	*file;
	int		ret;
	char	*tmp;

	ret = 0;
	file = ft_strnew(0);
	if ((fd = open(av, O_RDONLY)) == -1)
		ft_error_exit("Error: Please specify a valid scene file.\n");
	ft_init_env(e);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		file = ft_strjoin(tmp = file, line);
		free(tmp);
	}
	if (ft_parse_scene(file, e) == -1)
		ft_error_exit("Error: Please specify a valid scene file.\n");
	if (ret == -1)
		ft_error_exit("Error: Please specify a valid scene file.\n");
	free(line);
	free(file);
}

int		main(int ac, char **av)
{
	t_env e;

	if (ac != 2)
		return (0);
	ft_stock_scene(&e, av[1]);
/*	while (e.c_obj)
	{
		if (((t_nod *)e.c_obj)
		e.c_obj = e.c_obj->next;
	}*/
	ft_creat_win(&e);
	return (0);
}
