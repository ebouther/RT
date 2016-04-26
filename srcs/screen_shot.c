/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 18:01:02 by ascholle          #+#    #+#             */
/*   Updated: 2016/04/26 12:47:21 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_make_screen(t_env *e, char *name)
{
	int				fd;
	int				i;
	int				j;
	unsigned char	*p;
	unsigned char	*res;
	unsigned char	*sv;

	if ((fd = open(name, O_WRONLY | O_CREAT)) == -1)
		exit(-1);
	write(fd, "P6\n", 3);
	i = SIZE_W;
	j = SIZE_H;
	ft_putnbr_fd(i, fd);
	write(fd, " ", 1);
	ft_putnbr_fd(j, fd);
	write(fd, "\n255\n", 5);
	res = (unsigned char *)malloc(sizeof(unsigned char) * (SIZE_W * SIZE_H * 3));
	i = 0;
	p = (unsigned char*)(e->data);
	sv = res;
	while (i < SIZE_H)
	{
		j = 0;
		while (j < SIZE_W)
		{
			p += 2;
			*res = (int)*p;
			p--;
			res++;
			*res = (int)*p;
			p--;
			res++;
			*res = (int)*p;
			res++;
			p += 4;
			j++;
		}
		i++;
	}
	res = sv;
	write(fd, res, SIZE_H * SIZE_W * 3);
	free(res);
	close(fd);
}
