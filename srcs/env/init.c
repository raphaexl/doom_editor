/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 20:17:03 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/23 15:33:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/editor.h"

void	ft_add_player(t_game	*game)
{
	t_object	*object;

	object = ft_new_object((t_point){409, 500}, 250, 87, 512);
	object->tex_count = 8;
	object->size = 512;
	object->parent = ft_list_push(&(game->sectors[0].objects), ft_list_newnode(object));
	game->players = ft_new_player(object, &(game->sectors[0]), DEFAULT_WALLHEIGHT / 2, CONFIG_IMAGE_HEIGHT / 2);
	game->main_player = game->players;
	game->renderer.camera = game->main_player;
	game->main_player->pos->x = 4400;
	game->main_player->pos->y = 5000;
	game->main_player->height = PLAYER_HEIGHT;
	game->main_player->crouch_height = 0;
	object = ft_new_object((t_point){7000, 3000}, 500, 0, 1024);
	object->size = 500;
	object->tex_count = 1;
	object->properties = PROP_FIXED;
	object->parent = ft_list_push(&(game->sectors[0].objects), ft_list_newnode(object));
	for (Uint32 i = 0; i < game->sector_count; i++)
		game->sectors[i].brightness = 1;
}

void	ft_env_buttons_init(t_env *e)
{
	ft_button_push_back(&e->buttons, ft_button_new(e->sdl.renderer, "EDIT", 0xFF0000FF));
	ft_button_push_back(&e->buttons, ft_button_new(e->sdl.renderer, "RENDER", 0xFF0000FF));
}
