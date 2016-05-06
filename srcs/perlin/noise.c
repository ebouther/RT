/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 12:22:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/05/06 16:20:54 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

double	noise[height][width];

void generateNoise()
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			noise[y][x] = (rand() % 32768) / 32768.0;
}

double smoothNoise(double x, double y)
{
	double fractX = x - (int)x;
	double fractY = y - (int)y;

	int x1 = ((int)x + width) % width;
	int y1 = ((int)y + height) % height;

	int x2 = (x1 + width - 1) % width;
	int y2 = (y1 + height - 1) % height;

	double value = 0.0;

	value += fractX * fractY * noise[y1][x1];
	value += (1 - fractX) * fractY * noise[y1][x2];
	value += fractX * (1 - fractY) * noise[y2][x1];
	value += (1 - fractX) * (1 - fractY) * noise[y2][x2];

	return value;
}

double turbulence(double x, double y, double size)
{
	double value = 0.0, initialSize = size;

	while (size >= 1)
	{
		value += smoothNoise(x / size, y / size) * size;
		size /= 2.0;
	}

	return (128.0 * value / initialSize);

}

void	put_pixel(char **data, int x, int y, int color)
{
	int pos = 4 * y * width + 4 * x;
	(*data)[pos] = color >> 16;
	(*data)[pos + 1] = color >> 8;
	(*data)[pos + 2] = color;
}

t_color	get_pixel_color(char *data, int x, int y)
{
	int pos;

	pos = 4 * y * width + 4 * x;
	return ((t_color){ data[pos], data[pos + 1], data[pos + 2] });
}

#include <stdio.h>
char	*gen_noise(t_mlx *m)
{
	t_img	i;
	t_color	c;

	i.mlx_img = mlx_new_image (m->mlx_ptr, width, height);
	i.data = mlx_get_data_addr(i.mlx_img, &i.bpp, &i.size_line, &i.endian);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			c.r = c.g = c.b = (char)turbulence(x, y, 64);
			put_pixel(&i.data, x, y, (c.b << 16) + (c.g << 8) + c.r);
		}
	}
	mlx_put_image_to_window(m->mlx_ptr, m->mlx_win2, i.mlx_img, 0, 0);
	return (i.data);
}

char	*gen_wood(double xyPeriod, double turbPower, double turbSize, t_mlx *m)
{
	t_img	i;
	t_color	c;

	i.mlx_img = mlx_new_image (m->mlx_ptr, width, height);
	i.data = mlx_get_data_addr(i.mlx_img, &i.bpp, &i.size_line, &i.endian);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			double xValue = (x - width / 2) / (double)(width);
			double yValue = (y - height / 2) / (double)(height);
			double distValue = sqrt(xValue * xValue + yValue * yValue) + turbPower * turbulence(x, y, turbSize) / 256.0;
			double sineValue = 128.0 * fabs(sin(2 * xyPeriod * distValue * M_PI));
			c.r = (char)(80 + sineValue);
			c.g = (char)(30 + sineValue);
			c.b = 30;
			put_pixel(&i.data, x, y, (c.b << 16) + (c.g << 8) + c.r);
		}
	}
	mlx_put_image_to_window(m->mlx_ptr, m->mlx_win, i.mlx_img, 0, 0);
	return (i.data);
}

void	displacement_map(char *disp_map, char *img, int	w, int h, t_mlx *m)
{
	t_img i;

	int	xo;
	int	yo;
	int	scale_x;
	int	scale_y;

	scale_x = 1;
	scale_y = 1;
	
	i.mlx_img = mlx_new_image (m->mlx_ptr, width, height);
	i.data = mlx_get_data_addr(i.mlx_img, &i.bpp, &i.size_line, &i.endian);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
//			t_color c = get_pixel_color(disp_map, x, y);
//			xo = (c.r - 128) * scale_x / 256;
//			yo = (c.g - 128) * scale_y / 256;
//			printf("Xo : '%d' | Yo : '%d'\n", xo, yo);
//			if (xo >= width || yo >= height || xo < 0 || yo < 0)
//				put_pixel(&i.data, x, y, 0x00FF00);
//			else
			{
				t_color disp_c = get_pixel_color(img, x, y);
				if (disp_c.r < 0)
					disp_c.r = 0;
				if (disp_c.g < 0)
					disp_c.g = 0;
				if (disp_c.b < 0)
					disp_c.b = 0;
				put_pixel(&i.data, x, y, (disp_c.b << 16) + (disp_c.g << 8) + disp_c.r);
			}
		}
	}
	mlx_put_image_to_window(m->mlx_ptr, m->mlx_win3, i.mlx_img, 0, 0);
}

int	ft_hook_key(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx	m;

	srand(time(NULL));
	m.mlx_ptr = mlx_init();
	m.mlx_win = mlx_new_window (m.mlx_ptr, width, height, "Perlin Noise");
	m.mlx_win2 = mlx_new_window (m.mlx_ptr, width, height, "Perlin Noise 2");
	m.mlx_win3 = mlx_new_window (m.mlx_ptr, width, height, "Disp Map");
	m.mlx_win4 = mlx_new_window (m.mlx_ptr, width, height, "Gradient");

	generateNoise();
	char *data1 = gen_wood(12.0, 0.1, 32.0, &m);
	char *data2 = gen_noise(&m);
	int	fire_w = 980;
	int	fire_h = 575;
	
// Gradient
	t_img i;
	i.mlx_img = mlx_xpm_file_to_image(m.mlx_ptr, "fire.xpm", &fire_w, &fire_h);
	i.data = mlx_get_data_addr(i.mlx_img, &i.bpp, &i.size_line, &i.endian);
	mlx_put_image_to_window(m.mlx_ptr, m.mlx_win4, i.mlx_img, 0, 0);
//
	displacement_map(data2, i.data, width, height, &m);


	mlx_key_up_hook(m.mlx_win, ft_hook_key, NULL);
	mlx_key_up_hook(m.mlx_win2, ft_hook_key, NULL);
	mlx_key_up_hook(m.mlx_win3, ft_hook_key, NULL);
	mlx_loop(m.mlx_ptr);
	return 0;
}
