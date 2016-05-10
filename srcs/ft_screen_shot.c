/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 18:01:02 by ascholle          #+#    #+#             */
/*   Updated: 2016/05/10 11:41:50 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_set_img(unsigned char *p, unsigned char *res)
{
	int				i;
	int				j;

	i = 0;
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
}

void	ft_make_screen(t_env *e, char *name)
{
	int				fd;
	unsigned char	*res;

	if ((res = (unsigned char *)malloc(sizeof(unsigned char)
				* (SIZE_W * SIZE_H * 3))) == NULL)
		exit(-1);
	if ((fd = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
		exit(-1);
	write(fd, "P6\n", 3);
	ft_putnbr_fd((int)SIZE_W, fd);
	write(fd, " ", 1);
	ft_putnbr_fd((int)SIZE_H, fd);
	write(fd, "\n255\n", 5);
	ft_set_img((unsigned char*)(e->data), res);
	write(fd, res, SIZE_H * SIZE_W * 3);
	free(res);
	close(fd);
}
