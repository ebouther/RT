/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascholle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 18:01:02 by ascholle          #+#    #+#             */
/*   Updated: 2016/04/25 16:41:07 by ascholle         ###   ########.fr       */
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
	char			*c;

	if ((fd = open(name, O_WRONLY | O_CREAT)) == -1)
		exit(-1);
	write(fd, "P3\n", 3);
	i = SIZE_W;
	j = SIZE_H;
	ft_putnbr_fd(i, fd);
	write(fd, " ", 1);
	ft_putnbr_fd(j, fd);
	write(fd, "\n255", 4);
	(void)e;
	i = 0;
	p = (unsigned char*)(e->data);
	while (i < SIZE_H)
	{
		write(fd, "\n", 1);
		j = 0;
		while (j < SIZE_W)
		{
			p += 2;
			k = *p;
			c = ft_itoa(k);
			write(fd, c, ft_strlen(c));
			free(c);
			write(fd, " ", 1);
			p--;
			k = *p;
			c = ft_itoa(k);
			write(fd, c, ft_strlen(c));
			free(c);
			write(fd, " ", 1);
			p--;
			k = *p;
			c = ft_itoa(k);
			write(fd, c, ft_strlen(c));
			free(c);
			write(fd, " ", 1);
			p += 4;
			j++;
		}
		i++;
	ft_putnbr(i);
	ft_putchar('\n');
	}
	close(fd);
}
