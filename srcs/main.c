/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 13:52:18 by jbelless          #+#    #+#             */
/*   Updated: 2016/04/25 11:58:44 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*void	ft_read_scene(t_env *e, char *line)
{
	if (ft_atoi(line) == 0)
		ft_stock_cam(e, line);
	else if (ft_atoi(line) == 1)
		ft_stock_sphere(e, line);
	else if (ft_atoi(line) == 2)
		ft_stock_plan(e, line);
	else if (ft_atoi(line) == 3)
		ft_stock_cyl(e, line);
	else if (ft_atoi(line) == 4)
		ft_stock_cone(e, line);
	else if (ft_atoi(line) == -1)
		ft_stock_light(e, line);
}*/

void	ft_init_env(t_env *e)
{
	e->obj = NULL;
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
		exit(-1);
	ft_init_env(e);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		file = ft_strjoin(tmp = file, line);
		free(tmp);
	}
	if (ft_parse_scene(file, e) == -1)
		exit(-1);
	if (ret == -1)
		exit(-1);
	free(line);
	free(file);
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
