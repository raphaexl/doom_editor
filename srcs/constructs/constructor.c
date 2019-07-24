/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:41:11 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/22 14:41:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

t_player	*ft_new_player(t_object *object, t_sector *sector,
		int cam_height, int head_angle)
{
	t_player	*result;

	if (!(result = ft_memalloc(sizeof(t_player))))
		return (NULL);
	result->sector = sector;
	result->object = object;
	result->pos = &object->pos;
	result->cam_height = cam_height;
	result->head_angle = head_angle;
	return (result);
}

t_wall		*ft_new_wall(t_point p1, t_point p2, Uint32 texture, Uint32 propr)
{
	t_wall	*result;

	if (!(result = malloc(sizeof(t_wall))))
		return (NULL);
	result->p1 = p1;
	result->p2 = p2;
	result->texture = texture;
	result->properties = propr;
	return (result);
}

t_portal	*ft_new_portal(t_point p1, t_point p2, t_sector *dest, Uint32 propr)
{
	t_portal	*result;

	if (!(result = malloc(sizeof(t_portal))))
		return (NULL);
	result->wall.p1 = p1;
	result->wall.p2 = p2;
	result->wall.properties = propr;
	result->sector = dest;
	return (result);
}

t_object	*ft_new_object(t_point pos, Uint32 rad, Uint32 tex, Uint32 height)
{
	t_object	*result;

	if (!(result = malloc(sizeof(t_object))))
		return (NULL);
	result->pos = pos;
	result->radius = rad;
	result->size = rad;
	result->texture = tex;
	result->height = height;
	result->angle = 0;
	return (result);
}

t_sector	*ft_new_sector(int floor, int ceil, int floor_tex, int ceil_tex)
{
	t_sector	*result;

	if (!(result = ft_memalloc(sizeof(t_sector))))
		return (NULL);
	result->floor_height = floor;
	result->ceil_height = ceil;
	result->floor_tex = floor_tex;
	result->ceil_tex = ceil_tex;
	result->brightness = 1.0;
	return (result);
}
