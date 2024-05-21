#include "../cub3d.h"

static void	draw_pixel(uint8_t *pixel, t_color color)
{
	*(pixel++) = color.red;
	*(pixel++) = color.green;
	*(pixel++) = color.blue;
	*(pixel++) = color.alpha;
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	uint8_t		*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (x < img->width && y < img->height)
	{
		pixelstart = &img->pixels[(y * img->width + x) * BPP];
		if (color.alpha == 0)
		{
			//tmp
			// t_color color;
			// color.blue = 0xFF;
			// color.alpha = 0XFF;
			// draw_pixel(pixelstart, color);
			//tmp
			return ;
		}
		draw_pixel(pixelstart, color);
	}
	// if (!(x < img->width))
	// 	ft_putendl_fd("Pixel is out of bounds (axes x)", 2);
	// else if (!(y < img->height))
	// 	ft_putendl_fd("Pixel is out of bounds (axes y)", 2);
}

static double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

static double transform(double value)
{
	const double center = 0.4; // Center of transformation
	const double scale = 10.0; // Scale factor for significance
	double shifted = value - center; // Shift to make center at 0
	double transformed = sigmoid(scale * shifted); // Apply sigmoid function
	return transformed;
}

t_color convertColors(mlx_texture_t* texture, uint32_t index, double distance)
{
	t_color	color;

	color.red = texture->pixels[index];
	color.green = texture->pixels[index + 1];
	color.blue = texture->pixels[index + 2];
	color.alpha = texture->pixels[index + 3];
	distance = transform(distance / WINDOW_HEIGHT);
	color.red = distance * color.red;
	color.green = distance * color.green;
	color.blue = distance * color.blue;
	return color;
}
