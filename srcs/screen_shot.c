/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 18:01:02 by ascholle          #+#    #+#             */
/*   Updated: 2016/04/26 12:06:58 by ascholle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_make_screen(t_env *e, char *name)
{
	int				fd;
	int				i;
	int				j;
	int				k;
	unsigned char	*p;
	char			c;

	if ((fd = open(name, O_WRONLY | O_CREAT)) == -1)
		exit(-1);
	write(fd, "P6\n", 3);
	i = SIZE_W;
	j = SIZE_H;
	ft_putnbr_fd(i, fd);
	write(fd, " ", 1);
	ft_putnbr_fd(j, fd);
	write(fd, "\n255\n", 5);
	(void)e;
	i = 0;
	p = (unsigned char*)(e->data);
	while (i < SIZE_H)
	{
		j = 0;
		while (j < SIZE_W)
		{
			p += 2;
			k = *p;
			c = k;
			write(fd, &c, 1);
			p--;
			k = *p;
			c = k;
			write(fd, &c, 1);
			p--;
			k = *p;
			c = k;
			write(fd, &c, 1);
			p += 4;
			j++;
		}
		i++;
	ft_putnbr(i);
	ft_putchar('\n');
	}
	close(fd);
}
