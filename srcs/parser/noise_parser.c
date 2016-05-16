/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:22:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/16 16:39:23 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_pixel(char **data, int x, int y, int color)
{
	int	pos;

	pos = 4 * y * NOISE_WIDTH + 4 * x;
	(*data)[pos] = color >> 16;
	(*data)[pos + 1] = color >> 8;
	(*data)[pos + 2] = color;
}

t_color	get_pixel_color(char *data, int x, int y)
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

char		*gen_noise(double size)
{
	t_color	c;
	int		x;
	int		y;
	char	*data;
	double	**noise;
	int		i;

	i = 0;
	srand(time(NULL));
	noise = (double **)malloc(sizeof(double *) * NOISE_HEIGHT);
	while (i < NOISE_HEIGHT)
		noise[i++] = (double *)malloc(sizeof(double *) * NOISE_WIDTH);
	data = (char *)malloc(sizeof(char) * NOISE_WIDTH * NOISE_HEIGHT * 4);
	generate_noise(&noise);
	y = 0;
	while (y < NOISE_HEIGHT)
	{
		x = 0;
		while (x < NOISE_WIDTH)
		{
			c.r = (char)turbulence(x, y, size, &noise);
			c = (t_color){c.r, c.r, c.r};
			put_pixel(&data, x, y, ((int)c.b << 16) + ((int)c.g << 8) + (int)c.r);
			x++;
		}
		y++;
	}
	return (data);
}

char		*gen_wood(double xy_period, double turb_power, double turb_size)
{
	t_wood	w;
	char	*data;
	double	**noise;
	int		i;

	i = 0;
	srand(time(NULL));
	noise = (double **)malloc(sizeof(double *) * NOISE_HEIGHT);
	while (i < NOISE_HEIGHT)
		noise[i++] = (double *)malloc(sizeof(double *) * NOISE_WIDTH);
	generate_noise(&noise);
	data = (char *)malloc(sizeof(char) * NOISE_WIDTH * NOISE_HEIGHT * 4);
	ft_bzero((void *)data, NOISE_HEIGHT * NOISE_WIDTH);
	w.y = 0;
	while (w.y < NOISE_HEIGHT)
	{
		w.x = 0;
		while (w.x < NOISE_WIDTH)
		{
			w.x_val = (w.x - NOISE_WIDTH / 2) / (double)(NOISE_WIDTH);
			w.y_val = (w.y - NOISE_HEIGHT / 2) / (double)(NOISE_HEIGHT);
			w.dist_val = sqrt(w.x_val * w.x_val + w.y_val * w.y_val)
				+ turb_power * turbulence(w.x, w.y, turb_size, &noise) / 256.0;
			w.sine_val = 128.0 * fabs(sin(2 * xy_period * w.dist_val * M_PI));
			w.c.r = (char)(80 + w.sine_val);
			w.c.g = (char)(30 + w.sine_val);
			w.c.b = 30;
			put_pixel(&data, w.x, w.y, ((int)w.c.b << 16) + ((int)w.c.g << 8) + (int)w.c.r);
			w.x++;
		}
		w.y++;
	}
	return (data);
}
