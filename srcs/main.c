/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:52:18 by jbelless          #+#    #+#             */
/*   Updated: 2016/03/11 14:31:07 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_read_scene(t_env *e, char *line)
{
	static int i = 0;
	static int j = 0;

	if (ft_atoi(line) == 0)
		ft_stock_cam(e, line);
	else if (ft_atoi(line) == 1)
		ft_stock_sphere(e, line, &i);
	else if (ft_atoi(line) == 2)
		ft_stock_plan(e, line, &i);
	else if (ft_atoi(line) == 3)
		ft_stock_cyl(e, line, &i);
	else if (ft_atoi(line) == 4)
		ft_stock_cone(e, line, &i);
	else if (ft_atoi(line) == -1)
		ft_stock_light(e, line, &j);
}

void	ft_init_env(t_env *e)
{
	int i;

	i = 0;
	e->mlx = NULL;
	e->win = NULL;
	e->img = NULL;
	e->data = NULL;
	while (i < e->nb_obj)
	{
		e->obj[i].type.sph = 0;
		e->obj[i].type.plan = 0;
		e->obj[i].type.cone = 0;
		e->obj[i].type.cyl = 0;
		i++;
	}
}

void	ft_stock_scene(t_env *e, char *av)
{
	int		fd;
	char	*line;
	int		ret;

	ret = 0;
	if ((fd = open(av, O_RDONLY)) == -1)
		exit(0);
	if ((ret = get_next_line(fd, &line)) == -1)
		exit(0);
	if (*line < '0' || *line > '9')
		exit(0);
	e->nb_obj = ft_atoi(line);
	if ((ret = get_next_line(fd, &line)) == -1)
		exit(0);
	e->nb_light = ft_atoi(line);
	e->obj = (t_obj*)malloc(sizeof(t_obj) * e->nb_obj);
	e->light = (t_light*)malloc(sizeof(t_light) * e->nb_light);
	ft_init_env(e);
	while ((ret = get_next_line(fd, &line)) > 0)
		ft_read_scene(e, line);
	if (ret == -1)
		exit(0);
	free(line);
}

int		main(int ac, char **av)
{
	t_env e;

	if (ac != 2)
		return (0);
	ft_stock_scene(&e, av[1]);
	ft_creat_win(&e);
	return (0);
}
