/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 14:41:24 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/13 16:03:48 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

int	ft_hook_key(int keycode, t_mlx *m)
{
	static double	turb_size = 32.0;

	if (keycode == 15)
	{
		srand(time(NULL));
		generate_noise(&m->noise);
	}
	else if (keycode == 126)
		gen_noise(turb_size += 1, m);
	else if (keycode == 125)
		gen_noise(turb_size -= 1, m);
	else if (keycode == 53)
		exit(0);
	return (0);
}

void	put_pixel(char **data, int x, int y, int color)
{
	int pos = 4 * y * WIDTH + 4 * x;
	(*data)[pos] = color >> 16;
	(*data)[pos + 1] = color >> 8;
	(*data)[pos + 2] = color;
}

t_color	get_pixel_color(char *data, int x, int y)
{
	int pos;

	pos = 4 * y * WIDTH + 4 * x;
	return ((t_color){ data[pos], data[pos + 1], data[pos + 2]});
}

int main(int argc, char **argv)
{
	t_mlx	m;
	int		i;
	
	i = 0;
	m.noise = (double **)malloc(sizeof(double *) * HEIGHT);
	while (i < HEIGHT)
		m.noise[i++] = (double *)malloc(sizeof(double *) * WIDTH);
	srand(time(NULL));
	m.mlx_ptr = mlx_init();
	m.mlx_win = mlx_new_window (m.mlx_ptr, WIDTH, HEIGHT, "Perlin Noise");
	generate_noise(&m.noise);
	gen_noise(64.0, &m);
	mlx_key_up_hook(m.mlx_win, ft_hook_key, &m);
	mlx_loop(m.mlx_ptr);
	return (0);
}
