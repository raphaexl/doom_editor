/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 16:10:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 13:03:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_init_raycasting(t_raycast *raygen, double angle)
{
	raygen->plane = ft_vector_from_angle(PROJECTION_PLANE / 2,
			angle + M_PI / 2);
	raygen->direction = ft_vector_from_angle(PROJECTION_DISTANCE, angle);
	raygen->swipe.x = -raygen->plane.x;
	raygen->swipe.y = -raygen->plane.y;
	ft_normalise_vector(&raygen->swipe);
	raygen->ray.dir.x = raygen->direction.x + raygen->plane.x;
	raygen->ray.dir.y = raygen->direction.y + raygen->plane.y;
	raygen->ray.dist = 0;
	raygen->render_min = 0;
	raygen->render_max = CONFIG_IMAGE_HEIGHT;
}

void	ft_iter_ray(t_raycast *raygen)
{
	raygen->plane.x += raygen->swipe.x * CONFIG_RES_RATIO;
	raygen->plane.y += raygen->swipe.y * CONFIG_RES_RATIO;
	raygen->ray.dir.x = raygen->direction.x + raygen->plane.x;
	raygen->ray.dir.y = raygen->direction.y + raygen->plane.y;
	raygen->ray.dist = 0;
	raygen->render_min = 0;
	raygen->render_max = CONFIG_IMAGE_HEIGHT;
}

void	ft_raycast(t_graphic_render	*env)
{
	t_raycast	raygen;
	int			x;

	ft_bzero(&raygen, sizeof(t_raycast));
	raygen.ray.pos = *(env->camera->pos);
	ft_init_raycasting(&raygen, env->camera->object->angle);
	x = 0;
	while (x < PROJECTION_PLANE)
	{
		ft_intersect_ray(env, &raygen, env->camera->sector, x);
		ft_iter_ray(&raygen);
		x += CONFIG_RES_RATIO;
	}
}
