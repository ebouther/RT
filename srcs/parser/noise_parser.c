/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:22:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/01 13:52:50 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ft_init_gen(double ***noise, char **data)
{
	int		i;

	i = 0;
	srand(time(NULL));
	if ((*noise = (double **)malloc(sizeof(double *) * NOISE_HEIGHT)) != NULL)
		ft_error_exit("Cannot allocate memory.\n");
	while (i < NOISE_HEIGHT)
		(*noise)[i++] = (double *)malloc(sizeof(double *) * NOISE_WIDTH);
	generate_noise(noise);
	if ((*data = (char *)malloc(sizeof(char) * NOISE_WIDTH * NOISE_HEIGHT * 4))
			== NULL)
		ft_error_exit("Cannot allocate memory.\n");
	ft_bzero((void *)*data, NOISE_HEIGHT * NOISE_WIDTH);
}

char		*gen_noise(double size)
{
	t_color	c;
	int		x;
	int		y;
	char	*data;
	double	**noise;

	ft_init_gen(&noise, &data);
	y = 0;
	while (y < NOISE_HEIGHT)
	{
		x = 0;
		while (x < NOISE_WIDTH)
		{
			c.r = (char)turbulence(x, y, size, &noise);
			c = (t_color){c.r, c.r, c.r};
			put_pixel(&data, x, y, ((int)c.b << 16)
					+ ((int)c.g << 8) + (int)c.r);
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

	ft_init_gen(&noise, &data);
	w.y = -1;
	while (++w.y < NOISE_HEIGHT)
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
			put_pixel(&data, w.x, w.y, ((int)w.c.b << 16) + ((int)w.c.g << 8)
					+ (int)w.c.r);
			w.x++;
		}
	}
	return (data);
}
