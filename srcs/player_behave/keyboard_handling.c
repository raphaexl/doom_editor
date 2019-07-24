/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 22:20:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 09:11:39 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_apply_movement(t_player *player)
{
	player->pos->x += player->speed.x;
	player->pos->y += player->speed.y;
}

double	ft_movement_direction(t_player *player, t_input *input, int	*status)
{
	double angle;

	*status = 1;
	angle = player->object->angle;
	if (input->keys[KEY_UP])
	{
		if (input->keys[KEY_LEFT])
			angle += HALF_PI;
		else if (input->keys[KEY_RIGHT])
			angle -= HALF_PI;
	}
	else if (input->keys[KEY_DOWN])
	{
		angle += M_PI;
		if (input->keys[KEY_LEFT])
			angle -= HALF_PI;
		else if (input->keys[KEY_RIGHT])
			angle += HALF_PI;
	}
	else if (input->keys[KEY_RIGHT])
		angle -= HALF_PI;
	else if (input->keys[KEY_LEFT])
		angle += HALF_PI;
	else
		*status = 0;
	return (angle);
}

void	ft_movement_vector(t_player *player, double angle, double delta_time)
{
	t_vector	acceleration;

	acceleration = ft_vector_from_angle(PLAYER_VELOCITY, angle);
	acceleration.x *= delta_time;
	acceleration.y *= delta_time;
	player->speed.x += acceleration.x;
	player->speed.y += acceleration.y;
	acceleration.x = 0;
	acceleration.y = 0;
}

void	ft_apply_friction(t_player *player, double delta_time)
{
	player->speed.x -= player->speed.x * ((double)PLAYER_FRICTION * delta_time);
	player->speed.y -= player->speed.y * ((double)PLAYER_FRICTION * delta_time);
	if (player->speed.x < MIN_PLAYER_SPEED &&
			player->speed.x > -MIN_PLAYER_SPEED)
		player->speed.x = 0;
	if (player->speed.y < MIN_PLAYER_SPEED &&
			player->speed.y > -MIN_PLAYER_SPEED)
		player->speed.y = 0;
}

void	ft_apply_cam_movements(t_player *player, t_input *in)
{
	player->object->angle -= in->mousexrel * PLAYER_HEAD_SPEED;
	player->head_angle -= in->mouseyrel;
	player->head_angle = ft_limit(player->head_angle, 0, CONFIG_IMAGE_HEIGHT);
}

int		ft_isplayer_on_ground(t_player *player)
{
	int	height;
	int	floor_height;

	floor_height = -player->sector->floor_height;
	height = player->cam_height - player->height + player->crouch_height;
	if (height > floor_height)
		return (0);
	return (1);
}

void	ft_apply_jump(t_player *player, t_input *in)
{
	if (ft_isplayer_on_ground(player))
	{
		if (in->keys[KEY_UP] || in->keys[KEY_DOWN])
				 player->zspeed = (PLAYER_JUMP  / 2.0);
		else
			player->zspeed = 0;
		player->cam_height = player->height - player->crouch_height -
			player->sector->floor_height;
		if (in->keys[SDL_SCANCODE_SPACE])
			player->zspeed = PLAYER_JUMP;
	}
}

void	ft_apply_crouch(t_player *player, t_input *in)
{
	if (in->keys[SDL_SCANCODE_LSHIFT])
		player->crouch_height = player->height / 2;
}

int	ft_keyboard_handling(t_game *game)
{
	double	angle;
	int		status;

	angle = ft_movement_direction(game->main_player, &game->in, &status);
	if (status)
		ft_movement_vector(game->main_player, angle, game->delta_time);
	ft_apply_friction(game->main_player, game->delta_time);
	ft_apply_cam_movements(game->main_player, &game->in);
	ft_apply_crouch(game->main_player, &game->in);
	ft_apply_jump(game->main_player, &game->in);
	ft_player_behave(game->main_player, game);
	ft_apply_movement(game->main_player);
	return (0);
}
