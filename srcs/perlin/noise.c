#include <mlx.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define width 1000
#define height 1000

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

int main(int argc, char **argv)
{
	void	*mlx_ptr = mlx_init();
	void	*mlx_win = mlx_new_window ( mlx_ptr, width, height, "TEST" );
	void	*mlx_img = mlx_new_image (mlx_ptr, width, height);

	srand(time(NULL));

	int bpp;
	int size_line;
	int endian;

	char	*data = mlx_get_data_addr(mlx_img, &bpp, &size_line, &endian);

	char	r;
	char	g;
	char	b;

	double xyPeriod = 12.0; //number of rings
	double turbPower = 0.1; //makes twists
	double turbSize = 32.0; //initial size of the turbulence

	generateNoise();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			double xValue = (x - width / 2) / (double)(width);
			double yValue = (y - height / 2) / (double)(height);
			double distValue = sqrt(xValue * xValue + yValue * yValue) + turbPower * turbulence(x, y, turbSize) / 256.0;
			double sineValue = 128.0 * fabs(sin(2 * xyPeriod * distValue * 3.14159));
			r = (char)(80 + sineValue);
			g = (char)(30 + sineValue);
			b = 30;
			put_pixel(&data, x, y, (b << 16) + (g << 8) + r);
		}
	}
	mlx_put_image_to_window(mlx_ptr, mlx_win, mlx_img, 0, 0);
	mlx_loop(mlx_ptr);
	return 0;
}
