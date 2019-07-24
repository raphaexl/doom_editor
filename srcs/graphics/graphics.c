/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:07:25 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 13:03:04 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_draw_background_sky(t_graphic_render *env, int x, int y)
{
	int			center;
	int			mapy;
	t_texture	*sky;

	sky = &env->textures[ft_modulus(env->sky_texture, env->texture_count)];
	center = ((2 * M_PI - env->camera->object->angle) * sky->width) / (2 * M_PI);
	y = env->camera->head_angle;
	mapy = sky->height;
	while (y > 0)
	{
		x = 0;
		while (x < CONFIG_IMAGE_WIDTH)
		{
			ft_place_pixel(env->image, x, y, TEX_PIX(sky,
						ft_modulus(x + center - CONFIG_IMAGE_WIDTH / 2, sky->width),
						ft_modulus(mapy, sky->height)));
			x += CONFIG_RES_RATIO;
		}
		mapy -= CONFIG_RES_RATIO;
		y -= CONFIG_RES_RATIO;
	}
}

void	ft_render_background(t_graphic_render *env)
{
	Uint32	*table;
	int		j;

	table = env->image->pixels;
	j = CONFIG_IMAGE_WIDTH * (env->camera->head_angle);
	ft_draw_background_sky(env, 0, 0);
	while (j > 0 && j < CONFIG_IMAGE_HEIGHT * CONFIG_IMAGE_WIDTH)
		table[j++] = 0x696969;
}

int	ft_render_graphics(t_graphic_render	*env)
{
	ft_render_background(env);
	ft_raycast(env);
	return (1);
}
