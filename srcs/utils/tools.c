/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:08:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 17:00:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_point		ft_point(int x, int y)
{
	t_point po;

	po.x = x;
	po.y = y;
	return (po);
}

t_img	*ft_img_create(int w, int h, Uint32 color)
{
	t_img	*img;

	if ((img = (t_img *)malloc(sizeof(t_img))))
	{
		if (!(img->pixels = (Uint32 *)malloc(sizeof(Uint32) * w * h)))
		{
			ft_putendl_fd("Error pixels allocation ", 2);
			return (NULL);
		}
		img->w = w;
		img->h = h;
		ft_memset(img->pixels, color, sizeof(Uint32) * w * h);
	}
	return (img);
}

void	ft_sdl_put_pixel(t_img *img, int x, int y, int color)
{
	int		w;
	int		h;

	w = img->w;
	h = img->h;
	if (y >= 0 && y < h && x >= 0 && x < w)
		img->pixels[y * w + x] = color;
}

void	ft_sdl_clear_pixels(t_img *img, int color)
{
	int		size;
	int		i;

	size = img->w * img->h;
	i = -1;
	while (++i < size)
	{
		img->pixels[i] = color;
	}
}

Uint32	*ft_resize_b(Uint32	*pixels, int w1, int h1, int w2, int h2)
{
	Uint32	*new_pixels = NULL;

	new_pixels = (Uint32 *)malloc(sizeof(Uint32) * w2 * h2);
	Uint32	a = 0, b = 0, c = 0, d = 0, x = 0, y = 0, index = 0;
	float	x_ratio	= (float)(w1 - 1) / w2;
	float	y_ratio	= (float)(h1 - 1) / h2;
	float	x_diff = 0, y_diff = 0, blue = 0, red = 0, green = 0;
	int		offset = 0;

	for (int i = 0; i < h2; i++)
	{
		for (int j = 0; j < w2; j++)
		{
			x = (int) (x_ratio * j);
			y = (int) (y_ratio * i);
			x_diff = (x_ratio * j) - x;
			y_diff = (y_ratio * i) - y;
			index  = (y * w1 + x);
			a = pixels[index];
			b = pixels[index + 1];
			c = pixels[index + w1];
			d = pixels[index + w1 + 1];

			blue = (a & 0xff) * (1 - x_diff) * (1 - y_diff) + (b & 0xff) * 
				(x_diff) * (1 - y_diff) + (c & 0xff) * (y_diff) * (1 - x_diff) 
				+ (d & 0xff) * (x_diff * y_diff);
			green = ((a >> 8) & 0xff) * (1 - x_diff) * (1 - y_diff) + ((b >> 8) & 0xff) 
				* (x_diff) * (1 - y_diff) + (c & 0xff) * y_diff * (1 - x_diff) 
				+ ((d >> 8) & 0xff) * (x_diff * y_diff);
			red = ((a >> 16) & 0xff) * (1 - x_diff) * (1 - y_diff) + 
				((b >> 16) & 0xff) * x_diff * (1 - y_diff) + ((c >> 16) & 0xff) *
				(y_diff) * (1 - x_diff) + ((d >> 16) & 0xff) * (x_diff * y_diff);
			new_pixels[offset++] = 0xff000000 | ((((int)red) << 16) & 0xff0000) 
				| (((int)green << 8) & 0xff00) | ((int)blue);
		}
	}
	return (new_pixels);
}


