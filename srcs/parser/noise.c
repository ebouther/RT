/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 12:21:22 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 12:55:57 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		put_pixel(char **data, int x, int y, int color)
{
	int	pos;

	pos = 4 * y * NOISE_WIDTH + 4 * x;
	(*data)[pos] = color >> 16;
	(*data)[pos + 1] = color >> 8;
	(*data)[pos + 2] = color;
}

t_color		get_pixel_color(char *data, int x, int y)
{
	int pos;

	pos = 4 * y * NOISE_WIDTH + 4 * x;
	return ((t_color){data[pos], data[pos + 1], data[pos + 2]});
}

void		generate_noise(double ***noise)
{
	int	x;
	int	y;

	y = 0;
	while (y < NOISE_HEIGHT)
	{
		x = 0;
		while (x < NOISE_WIDTH)
			(*noise)[y][x++] = (rand() % 32768) / 32768.0;
		y++;
	}
}

double		smooth_noise(double x, double y, double ***noise)
{
	t_smooth s;

	s.value = 0.0;
	s.fract_x = x - (int)x;
	s.fract_y = y - (int)y;
	s.x1 = ((int)x + NOISE_WIDTH) % NOISE_WIDTH;
	s.y1 = ((int)y + NOISE_HEIGHT) % NOISE_HEIGHT;
	s.x2 = (s.x1 + NOISE_WIDTH - 1) % NOISE_WIDTH;
	s.y2 = (s.y1 + NOISE_HEIGHT - 1) % NOISE_HEIGHT;
	s.value += s.fract_x * s.fract_y * (*noise)[s.y1][s.x1];
	s.value += (1 - s.fract_x) * s.fract_y * (*noise)[s.y1][s.x2];
	s.value += s.fract_x * (1 - s.fract_y) * (*noise)[s.y2][s.x1];
	s.value += (1 - s.fract_x) * (1 - s.fract_y) * (*noise)[s.y2][s.x2];
	return (s.value);
}

double		turbulence(double x, double y, double size, double ***noise)
{
	double	value;
	double	initial_size;

	value = 0.0;
	initial_size = size;
	while (size >= 1)
	{
		value += smooth_noise(x / size, y / size, noise) * size;
		size /= 2.0;
	}
	return (128.0 * value / initial_size);
}

