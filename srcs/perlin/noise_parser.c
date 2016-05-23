/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:22:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/13 18:23:09 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

void		generate_noise(double ***noise)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
	s.x1 = ((int)x + WIDTH) % WIDTH;
	s.y1 = ((int)y + HEIGHT) % HEIGHT;
	s.x2 = (s.x1 + WIDTH - 1) % WIDTH;
	s.y2 = (s.y1 + HEIGHT - 1) % HEIGHT;
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

char		*gen_noise(double size, t_mlx *m)
{
	t_color	c;
	int		x;
	int		y;
	char	*data;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.r = (char)turbulence(x, y, size, &m->noise);
			c = (t_color){c.r, c.r, c.r};
			put_pixel(&data, x, y, (c.b << 16) + (c.g << 8) + c.r);
			x++;
		}
		y++;
	}
	return (data);
}

char		*gen_wood(double xy_period, double turb_power, double turb_size,
				t_mlx *m)
{
	t_wood	w;
	char	*data;

	w.y = 0;
	while (w.y < HEIGHT)
	{
		w.x = 0;
		while (w.x < WIDTH)
		{
			w.x_val = (w.x - WIDTH / 2) / (double)(WIDTH);
			w.y_val = (w.y - HEIGHT / 2) / (double)(HEIGHT);
			w.dist_val = sqrt(w.x_val * w.x_val + w.y_val * w.y_val)
				+ turb_power * turbulence(w.x, w.y, turb_size, &m->noise) / 256.0;
			w.sine_val = 128.0 * fabs(sin(2 * xy_period * w.dist_val * M_PI));
			w.c.r = (char)(80 + w.sine_val);
			w.c.g = (char)(30 + w.sine_val);
			w.c.b = 30;
			put_pixel(&data, w.x, w.y, (w.c.b << 16) + (w.c.g << 8) + w.c.r);
			w.x++;
		}
		w.y++;
	}
	return (data);
}
