#include "../cub3d.h"

static void	draw_pixel(uint8_t *pixel, t_color color)
{
	*(pixel++) = color.red;
	*(pixel++) = color.green;
	*(pixel++) = color.blue;
	*(pixel++) = color.alpha;
}

static void	draw_pixel_uint(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = color >> 24;
	*(pixel++) = color >> 16;
	*(pixel++) = color >> 8;
	*(pixel++) = color & 0xFF;
}

void	put_pixel_uint(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t		*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (x < img->width - 1 && y < img->height - 1)
	{
		pixelstart = &img->pixels[(y * img->width + x) * BPP];
		if (color & 0xFF)
			draw_pixel_uint(pixelstart, color);
	}
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, t_color color)
{
	uint8_t		*pixelstart;

	if (!img)
		ft_putendl_fd("Image does not exist", 2);
	if (x < img->width - 1 && y < img->height - 1)
	{
		pixelstart = &img->pixels[(y * img->width + x) * BPP];
		if (color.alpha != 0)
			draw_pixel(pixelstart, color);
	}
	// if (!(x < img->width))
	// 	ft_putendl_fd("Pixel is out of bounds (axes x)", 2);
	// else if (!(y < img->height))
	// 	ft_putendl_fd("Pixel is out of bounds (axes y)", 2);
}

static float sigmoid(float x)
{
	return 1 / (1 + exp(-x));
}

static float transform(float value)
{
	const float center = 0.4; // Center of transformation
	const float scale = 10.0; // Scale factor for significance
	float shifted = value - center; // Shift to make center at 0
	float transformed = sigmoid(scale * shifted); // Apply sigmoid function
	return transformed;
}

t_color convertColors(mlx_texture_t* texture, uint32_t index, float distance)
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
